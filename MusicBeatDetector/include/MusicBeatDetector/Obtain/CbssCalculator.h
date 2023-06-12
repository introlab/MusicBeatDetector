#ifndef MUSIC_BEAT_DETECTOR_OBTAIN_CBSS_CALCULATOR_H
#define MUSIC_BEAT_DETECTOR_OBTAIN_CBSS_CALCULATOR_H

#include <MusicBeatDetector/Utils/ClassMacro.h>

#include <armadillo>

#include <cstddef>

namespace introlab
{
    class CbssCalculator
    {
        float m_ossSamplingFrequency;

        arma::fvec m_cbss;
        arma::fvec m_vFloat;
        arma::uvec m_v;
        arma::fvec m_w;

    public:
        CbssCalculator(float ossSamplingFrequency = 44100.0 / 128, float minBpm = 50);
        virtual ~CbssCalculator();

        DECLARE_NOT_COPYABLE(CbssCalculator);
        DECLARE_NOT_MOVABLE(CbssCalculator);

        float calculate(float bpm, float oss);

    private:
        float calculatePhy(std::size_t beatPeriod);
    };
}

#endif
