#include <MusicBeatDetector/Obtain/BpmEstimator.h>

#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>
#include <MusicBeatDetector/Utils/Math/Math.h>

#include <chrono>
#include <limits>

using namespace introlab;
using namespace std;

BpmEstimator::BpmEstimator(
    float ossSamplingFrequency,
    size_t ossWindowSize,
    float minBpm,
    float maxBpm,
    size_t candidateCount)
    : m_ossSamplingFrequency(ossSamplingFrequency),
      m_crossCorrelationCalculator(ossWindowSize),
      m_candidateCount(candidateCount)
{
    if (minBpm <= 0 || maxBpm <= 0)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("minBpm and maxBpm must be greater than 0");
    }
    if (maxBpm <= minBpm)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("maxBpm must be greater than minBpm");
    }
    if (m_candidateCount < 1)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("candidateCount must be at least 1");
    }

    m_minLag = static_cast<size_t>(60 * ossSamplingFrequency / maxBpm);
    m_maxLag = static_cast<size_t>(60 * ossSamplingFrequency / minBpm);
    if (ossWindowSize <= m_minLag || ossWindowSize <= m_maxLag)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("ossWindowSize must be greater than minLag and maxLag");
    }

    m_oss = arma::zeros<arma::fvec>(ossWindowSize);
}

BpmEstimator::~BpmEstimator() {}

float BpmEstimator::estimate(float oss)
{
    m_oss = arma::join_cols(m_oss(arma::span(1, m_oss.n_elem - 1)), arma::fvec({oss}));
    arma::fvec enhancedAutoCorrelation = calculateEnhancedAutoCorrelation();

    vector<size_t> candidateLags = calculateCandidateLags(enhancedAutoCorrelation);
    size_t bestLag = getBestLag(candidateLags);

    return 60 * m_ossSamplingFrequency / bestLag;
}

arma::fvec BpmEstimator::calculateEnhancedAutoCorrelation()
{
    arma::fvec meanSubtractedOss = m_oss - arma::mean(m_oss);
    arma::fvec a = m_crossCorrelationCalculator.calculate(meanSubtractedOss, meanSubtractedOss);

    a = a(arma::span(m_oss.n_elem - 1, a.n_elem - 1));

    arma::fvec stretched2xA = a.elem(arma::regspace<arma::uvec>(0, 2, a.n_elem - 1));
    stretched2xA = arma::join_cols(stretched2xA, arma::zeros<arma::fvec>(a.n_elem / 2));

    arma::fvec stretched4xA = a.elem(arma::regspace<arma::uvec>(0, 4, a.n_elem - 1));
    stretched4xA = arma::join_cols(stretched4xA, arma::zeros<arma::fvec>(3 * a.n_elem / 4));

    return a + stretched2xA + stretched4xA;
}

vector<size_t> BpmEstimator::calculateCandidateLags(const arma::fvec& enhancedAutoCorrelation)
{
    vector<size_t> candidateLags;
    candidateLags.reserve(m_candidateCount);

    arma::fvec enhancedAutoCorrelationCopy = enhancedAutoCorrelation(arma::span(m_minLag, m_maxLag));

    while (candidateLags.size() < m_candidateCount)
    {
        size_t maxIndex = enhancedAutoCorrelationCopy.index_max();
        enhancedAutoCorrelationCopy(maxIndex) = -numeric_limits<float>::max();
        candidateLags.push_back(maxIndex + m_minLag);
    }

    return candidateLags;
}

size_t BpmEstimator::getBestLag(const vector<size_t>& candidateLags)
{
    arma::fvec maxScores = arma::zeros<arma::fvec>(candidateLags.size());
    arma::fvec varScores = arma::zeros<arma::fvec>(candidateLags.size());

    for (size_t i = 0; i < candidateLags.size(); i++)
    {
        CandidateScore score = calcultateCandidateLagScore(candidateLags[i]);
        maxScores(i) = score.maxScore;
        varScores(i) = score.varScore;
    }

    arma::fvec scores = maxScores / arma::sum(maxScores) + varScores / arma::sum(varScores);
    return candidateLags[scores.index_max()];
}

BpmEstimator::CandidateScore BpmEstimator::calcultateCandidateLagScore(size_t lag)
{
    constexpr size_t PulseCount = 4;
    constexpr size_t PulseSequenceCount = 3;
    constexpr float PulseSequencePeriodes[PulseSequenceCount] = {1, 1.5, 2};
    constexpr float PulseSequenceValues[PulseSequenceCount] = {1, 0.5, 0.5};

    arma::fvec pulseTrain = arma::zeros<arma::fvec>(m_oss.n_elem);
    for (size_t i = 0; i < PulseSequenceCount; i++)
    {
        for (size_t j = 0; j < PulseCount; j++)
        {
            size_t pulseIndex = static_cast<size_t>(j * PulseSequencePeriodes[i] * lag);
            if (pulseIndex < pulseTrain.n_elem)
            {
                pulseTrain(pulseIndex) += PulseSequenceValues[i];
            }
        }
    }

    arma::fvec a = m_crossCorrelationCalculator.calculate(m_oss, pulseTrain);

    CandidateScore score;
    score.maxScore = a.max();
    score.varScore = arma::var(a);

    return score;
}
