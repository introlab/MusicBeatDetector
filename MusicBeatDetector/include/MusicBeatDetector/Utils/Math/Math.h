#ifndef MUSIC_BEAT_DETECTOR_UTILS_MATH_MATH_H
#define MUSIC_BEAT_DETECTOR_UTILS_MATH_MATH_H

#include <armadillo>
#include <fftw3.h>

#include <cstddef>

namespace introlab
{
    template<class T>
    inline T hamming(std::size_t length)
    {
        const std::size_t N = length - 1;
        T n = arma::regspace<T>(0, N);
        return 0.54 - 0.46 * arma::cos(2 * M_PI * n / N);
    }

    inline arma::fvec fftShift(const arma::fvec& a) { return arma::shift(a, a.n_elem / 2); }

    inline arma::fvec crossCorrelation(const arma::fvec& a, const arma::fvec& b)
    {
        return arma::conv(a, arma::reverse(b));
    }
}

#endif
