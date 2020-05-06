#include <MusicBeatDetector/Obtain/OssCalculator.h>

#include <Utils/Exception/NotSupportedException.h>
#include <Utils/Math/Math.h>

#include <limits>

using namespace introlab;
using namespace std;

OssCalculator::OssCalculator(size_t frameSampleCount, size_t ossWindowSize, size_t fluxHammingSize) :
    m_frameSampleCount(frameSampleCount),
    m_fluxShiftRegister(fluxHammingSize),
    m_frame(1, frameSampleCount)
{
    if (ossWindowSize < frameSampleCount)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("ossWindowSize must be greater than or equal to frameSampleCount");
    }
    if ((ossWindowSize % frameSampleCount) != 0)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("frameSampleCount must be a multiple of ossWindowSize");
    }

    m_signalHamming = hamming<arma::fvec>(ossWindowSize);
    m_fluxHamming = hamming<arma::fvec>(fluxHammingSize);

    m_lastSpectrum = arma::zeros<arma::fvec>(ossWindowSize);
    m_windowedSignal = arma::zeros<arma::fvec>(ossWindowSize);
}

OssCalculator::~OssCalculator()
{
}

float OssCalculator::calculate(const PcmAudioFrame& frame)
{
    if (frame.channelCount() != 1 || frame.sampleCount() != m_frameSampleCount)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("Invalid frame");
    }

    m_frame = frame;
    arma::fvec frameVec(m_frame.data(), m_frameSampleCount);
    m_windowedSignal = arma::join_cols(m_windowedSignal(arma::span(m_frameSampleCount, m_windowedSignal.n_elem - 1)),
        frameVec);

    float flux = calculateFlux();
    m_fluxShiftRegister.shift(flux);

    return calculateOss();
}

float OssCalculator::calculateFlux()
{
    const float Gamma = 25;
    const float Threshold = 3.7;

    arma::cx_fvec complexSignal = arma::conv_to<arma::cx_fvec>::from(m_windowedSignal % m_signalHamming);
    arma::cx_fvec complexSpectrum;
    fft(complexSignal, complexSpectrum);

    arma::fvec spectrum = arma::abs(complexSpectrum);
    spectrum = arma::clamp(spectrum, Threshold, numeric_limits<float>::max());
    spectrum -= Threshold;
    spectrum /= arma::max(spectrum);
    spectrum = arma::log10(1 + Gamma * spectrum);
    spectrum /= arma::max(spectrum);

    float flux = arma::sum(arma::abs(m_lastSpectrum - spectrum));
    m_lastSpectrum = spectrum;

    return std::isfinite(flux) ? flux : 0;
}

float OssCalculator::calculateOss()
{
    float oss = 0;
    for (int64_t i = 0; i < m_fluxShiftRegister.size(); i++)
    {
        oss += m_fluxShiftRegister[i] * m_fluxHamming(i);
    }

    return oss;
}
