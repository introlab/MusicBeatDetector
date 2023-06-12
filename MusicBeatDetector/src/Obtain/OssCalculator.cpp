#include <MusicBeatDetector/Obtain/OssCalculator.h>

#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>
#include <MusicBeatDetector/Utils/Math/Math.h>

#include <limits>

using namespace introlab;
using namespace std;

OssCalculator::OssCalculator(size_t frameSampleCount, size_t ossWindowSize, size_t fluxHammingSize)
    : m_fftCalculator(ossWindowSize),
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

OssCalculator::~OssCalculator() {}

float OssCalculator::calculate(const PcmAudioFrame& frame)
{
    if (frame.channelCount() != 1 || frame.sampleCount() != m_frameSampleCount)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("Invalid frame");
    }

    m_frame = frame;
    arma::fvec frameVec(m_frame.data(), m_frameSampleCount);
    m_windowedSignal =
        arma::join_cols(m_windowedSignal(arma::span(m_frameSampleCount, m_windowedSignal.n_elem - 1)), frameVec);

    float flux = calculateFlux();
    m_fluxShiftRegister.shift(flux);

    return calculateOss();
}

float OssCalculator::calculateFlux()
{
    const float Gamma = 25;
    const float Threshold = 3.7;

    m_complexSignal = arma::conv_to<arma::cx_fvec>::from(m_windowedSignal % m_signalHamming);
    m_fftCalculator.fft(m_complexSignal, m_complexSpectrum);

    m_spectrum = arma::abs(m_complexSpectrum);
    m_spectrum = arma::clamp(m_spectrum, Threshold, numeric_limits<float>::max());
    m_spectrum -= Threshold;
    m_spectrum /= arma::max(m_spectrum) + numeric_limits<float>::epsilon();
    m_spectrum = arma::log10(1 + Gamma * m_spectrum);
    m_spectrum /= arma::max(m_spectrum) + numeric_limits<float>::epsilon();

    float flux = arma::sum(arma::abs(m_lastSpectrum - m_spectrum));
    m_lastSpectrum = m_spectrum;

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
