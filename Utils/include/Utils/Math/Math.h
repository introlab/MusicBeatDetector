#ifndef UTILS_MATH_MATH_H
#define UTILS_MATH_MATH_H

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

    inline void fft(arma::cx_fvec& x, arma::cx_fvec& y)
    {
        if (y.n_elem != x.n_elem)
        {
            y = arma::zeros<arma::cx_fvec>(x.n_elem);
        }

        fftwf_plan plan = fftwf_plan_dft_1d(x.n_elem,
            reinterpret_cast<fftwf_complex*>(x.memptr()),
            reinterpret_cast<fftwf_complex*>(y.memptr()),
            FFTW_FORWARD,
            FFTW_ESTIMATE);
        fftwf_execute(plan);
        fftwf_destroy_plan(plan);
    }

    inline void ifft(arma::cx_fvec& x, arma::cx_fvec& y)
    {
        if (y.n_elem != x.n_elem)
        {
            y = arma::zeros<arma::cx_fvec>(x.n_elem);
        }

        fftwf_plan plan = fftwf_plan_dft_1d(x.n_elem,
            reinterpret_cast<fftwf_complex*>(x.memptr()),
            reinterpret_cast<fftwf_complex*>(y.memptr()),
            FFTW_BACKWARD,
            FFTW_ESTIMATE);
        fftwf_execute(plan);
        fftwf_destroy_plan(plan);

        y /= y.n_elem;
    }

    inline arma::fvec fftShift(const arma::fvec& a)
    {
        return arma::shift(a, a.n_elem / 2);
    }

    inline arma::fvec crossCorrelation(const arma::fvec& a, const arma::fvec& b)
    {
        return arma::conv(a, arma::reverse(b));
    }
}

#endif
