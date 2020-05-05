#ifndef MUSIC_BEAT_DETECTOR_OBTAIN_CBSS_CALCULATOR_H
#define MUSIC_BEAT_DETECTOR_OBTAIN_CBSS_CALCULATOR_H

#include <armadillo>

#include <cstddef>

namespace introlab
{
    class CbssCalculator
    {
        float m_ossSamplingFrequency;

        arma::fvec m_cbss;

    public:
        CbssCalculator(float ossSamplingFrequency = 44100.0 / 128, float minBpm = 50);
        virtual ~CbssCalculator();

        float calculate(float bpm, float oss);

    private:
        float calculatePhy(std::size_t beatPeriod);
    };
}

#endif