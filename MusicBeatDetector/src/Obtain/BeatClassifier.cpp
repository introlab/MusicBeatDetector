#include <MusicBeatDetector/Obtain/BeatClassifier.h>

#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>
#include <MusicBeatDetector/Utils/Math/Math.h>

#include <cmath>

using namespace introlab;
using namespace std;

static constexpr size_t PulseCount = 2;

BeatClassifier::BeatClassifier(float ossSamplingFrequency, float minBpm)
    : m_ossSamplingFrequency(ossSamplingFrequency),
      m_classificationCountAfterBeat(0)
{
    if (minBpm <= 0)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("minLag must be greater than 0");
    }

    size_t maxLag = static_cast<size_t>(60 * ossSamplingFrequency / minBpm);
    m_cbss = arma::zeros<arma::fvec>(PulseCount * maxLag);
}

BeatClassifier::~BeatClassifier() {}

bool BeatClassifier::classify(float bpm, float cbss)
{
    constexpr size_t CrossCorrelationExtraPadding = 10;
    constexpr float BeatTolerance = 0.95;

    size_t beatPeriod = static_cast<size_t>(60 * m_ossSamplingFrequency / bpm);
    m_cbss = arma::join_cols(arma::fvec({cbss}), m_cbss(arma::span(0, m_cbss.n_elem - 2)));
    arma::fvec pulseTrain = generatePulseTrain(beatPeriod);

    arma::span crossCorrelationSpan(
        0,
        min(static_cast<size_t>(m_cbss.n_elem - 1), beatPeriod + CrossCorrelationExtraPadding));
    arma::fvec a = crossCorrelation(m_cbss(crossCorrelationSpan), pulseTrain(crossCorrelationSpan));
    a = a(arma::span(m_cbss(crossCorrelationSpan).n_elem - 1, a.n_elem - 1));

    bool isBeat = a.index_max() == 0 && m_classificationCountAfterBeat > (BeatTolerance * beatPeriod);
    m_classificationCountAfterBeat++;
    if (isBeat)
    {
        m_classificationCountAfterBeat = 0;
    }

    return isBeat;
}

arma::fvec BeatClassifier::generatePulseTrain(size_t beatPeriod)
{
    arma::fvec pulseTrain = arma::zeros<arma::fvec>(m_cbss.n_elem);
    for (size_t i = 0; i < PulseCount; i++)
    {
        pulseTrain(i * beatPeriod) = 1;
    }

    return pulseTrain;
}
