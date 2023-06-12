#ifndef MUSIC_BEAT_DETECTOR_UTILS_MATH_FFT_CALCULATOR_H
#define MUSIC_BEAT_DETECTOR_UTILS_MATH_FFT_CALCULATOR_H

#include <armadillo>
#include <fftw3.h>

namespace introlab
{
    class FftCalculator
    {
        arma::cx_fvec m_x;
        arma::cx_fvec m_y;

        fftwf_plan m_fftPlan;
        fftwf_plan m_ifftPlan;

    public:
        explicit FftCalculator(size_t size);
        virtual ~FftCalculator();

        void fft(arma::cx_fvec& x, arma::cx_fvec& y);
        void ifft(arma::cx_fvec& x, arma::cx_fvec& y);
    };
}

#endif
