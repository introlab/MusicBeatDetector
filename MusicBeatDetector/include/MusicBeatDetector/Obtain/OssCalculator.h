#ifndef MUSIC_BEAT_DETECTOR_OBTAIN_OSS_CALCULATOR_H
#define MUSIC_BEAT_DETECTOR_OBTAIN_OSS_CALCULATOR_H

#include <Utils/ClassMacro.h>
#include <Utils/Data/PcmAudioFrame.h>
#include <Utils/Data/AudioFrame.h>
#include <Utils/Data/ShiftRegister.h>

#include <armadillo>

#include <cstddef>

namespace introlab
{
    class OssCalculator
    {
        std::size_t m_frameSampleCount;
        arma::fvec m_signalHamming;
        arma::fvec m_fluxHamming;

        arma::fvec m_lastSpectrum;
        ShiftRegister<float> m_fluxShiftRegister;

        arma::fvec m_windowedSignal;
        AudioFrame<float> m_frame;

    public:
        OssCalculator(std::size_t frameSampleCount = 128,
                      std::size_t ossWindowSize = 1024,
                      std::size_t fluxHammingSize = 15);
        virtual ~OssCalculator();

        DECLARE_NOT_COPYABLE(OssCalculator);
        DECLARE_NOT_MOVABLE(OssCalculator);

        float calculate(const PcmAudioFrame& frame);

    private:
        float calculateFlux();
        float calculateOss();
    };
}

#endif
