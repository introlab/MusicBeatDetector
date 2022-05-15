#ifndef MUSIC_BEAT_DETECTOR_UTILS_MATH_CROSS_CORRELATION_CALCULATOR_H
#define MUSIC_BEAT_DETECTOR_UTILS_MATH_CROSS_CORRELATION_CALCULATOR_H

#include <armadillo>
#include <fftw3.h>

#include <cstddef>

namespace introlab
{
    class CrossCorrelationCalculator;

    class CircularCrossCorrelationCalculator
    {
        arma::fvec m_a;
        arma::cx_fvec m_A;
        arma::fvec m_b;
        arma::cx_fvec m_B;
        arma::fvec m_c;
        arma::cx_fvec m_C;

        fftwf_plan m_fftPlanA;
        fftwf_plan m_fftPlanB;
        fftwf_plan m_ifftPlan;

    public:
        CircularCrossCorrelationCalculator(std::size_t size);
        virtual ~CircularCrossCorrelationCalculator();

        arma::fvec calculate(const arma::fvec& a, const arma::fvec& b);

    private:
        arma::fvec calculate();

        friend CrossCorrelationCalculator;
    };

    class CrossCorrelationCalculator
    {
        std::size_t m_size;
        std::size_t m_circularCrossCorrelationSize;
        CircularCrossCorrelationCalculator m_circularCrossCorrelationCalculator;

    public:
        CrossCorrelationCalculator(std::size_t size);
        virtual ~CrossCorrelationCalculator();

        arma::fvec calculate(const arma::fvec& a, const arma::fvec& b);
    };

    template<class T>
    T nextPower(T v, T p)
    {
        if (v == 0)
        {
            return 0;
        }

        T power = 1;
        while (power < v)
        {
            power *= p;
        }

        return power;
    }
}

#endif
