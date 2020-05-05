#ifndef UTILS_MATH_CROSS_CORRELATION_CALCULATOR_H
#define UTILS_MATH_CROSS_CORRELATION_CALCULATOR_H

#include <armadillo>
#include <fftw3.h>

#include <cstddef>

namespace introlab
{
    class CircularCrossCorrelationCalculator
    {
        arma::cx_fvec m_a;
        arma::cx_fvec m_A;
        arma::cx_fvec m_b;
        arma::cx_fvec m_B;
        arma::cx_fvec m_c;
        arma::cx_fvec m_C;

        fftwf_plan m_fftPlanA;
        fftwf_plan m_fftPlanB;
        fftwf_plan m_ifftPlan;

    public:
        CircularCrossCorrelationCalculator(std::size_t size);
        virtual ~CircularCrossCorrelationCalculator();

        arma::fvec calculate(const arma::fvec& a, const arma::fvec& b);
    };

    class CrossCorrelationCalculator
    {
        std::size_t m_size;
        arma::fvec m_a;
        arma::fvec m_b;
        CircularCrossCorrelationCalculator m_circularCrossCorrelationCalculator;

    public:
        CrossCorrelationCalculator(std::size_t size);
        virtual ~CrossCorrelationCalculator();

        arma::fvec calculate(const arma::fvec& a, const arma::fvec& b);
    };
}

#endif
