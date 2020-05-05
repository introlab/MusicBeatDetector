#include <MusicBeatDetector/Obtain/CbssCalculator.h>

#include <Utils/Exception/NotSupportedException.h>

using namespace introlab;
using namespace std;

CbssCalculator::CbssCalculator(float ossSamplingFrequency, float minBpm) :
    m_ossSamplingFrequency(ossSamplingFrequency)
{
    if (minBpm <= 0)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("minLag must be greater than 0");
    }

    size_t maxLag = static_cast<size_t>(60 * ossSamplingFrequency / minBpm);
    m_cbss = arma::zeros<arma::fvec>(4 * maxLag);
}

CbssCalculator::~CbssCalculator()
{
}

float CbssCalculator::calculate(float bpm, float oss)
{
    constexpr float Alpha = 0.9;
    size_t beatPeriod = static_cast<size_t>(60 * m_ossSamplingFrequency / bpm);
    float phy = calculatePhy(beatPeriod);

    float newCbss = (1 - Alpha) * oss + Alpha * phy;
    m_cbss = arma::join_cols(m_cbss(arma::span(1, m_cbss.n_elem - 1)), arma::fvec({newCbss}));

    return newCbss;
}

float CbssCalculator::calculatePhy(size_t beatPeriod)
{
    constexpr float Eta = 10;
    float beatPeriodFloat = beatPeriod;
    arma::fvec vFloat = arma::regspace<arma::fvec>(-2 * beatPeriodFloat, -beatPeriodFloat / 2);
    arma::uvec v = arma::conv_to<arma::uvec>::from(vFloat);

    arma::fvec w = arma::exp(-Eta * arma::square(arma::log(-vFloat / beatPeriod)) / 2);

    return (m_cbss.elem(m_cbss.n_elem - v - 1) % w).max();
}
