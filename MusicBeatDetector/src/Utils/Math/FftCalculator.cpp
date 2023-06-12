#include <MusicBeatDetector/Utils/Math/FftCalculator.h>

#include <MusicBeatDetector/Utils/Exception/InvalidValueException.h>

using namespace introlab;
using namespace std;

FftCalculator::FftCalculator(size_t size)
{
    m_x.zeros(size);
    m_y.zeros(size);

    m_fftPlan = fftwf_plan_dft_1d(
        static_cast<int>(size),
        reinterpret_cast<fftwf_complex*>(m_x.memptr()),
        reinterpret_cast<fftwf_complex*>(m_y.memptr()),
        FFTW_FORWARD,
        FFTW_PATIENT);
    m_ifftPlan = fftwf_plan_dft_1d(
        static_cast<int>(size),
        reinterpret_cast<fftwf_complex*>(m_x.memptr()),
        reinterpret_cast<fftwf_complex*>(m_y.memptr()),
        FFTW_BACKWARD,
        FFTW_PATIENT);
}

FftCalculator::~FftCalculator()
{
    fftwf_destroy_plan(m_fftPlan);
    fftwf_destroy_plan(m_ifftPlan);
}

void FftCalculator::fft(arma::cx_fvec& x, arma::cx_fvec& y)
{
    if (x.n_elem != m_x.n_elem)
    {
        THROW_INVALID_VALUE_EXCEPTION("X is not compatible with the constructor size", "");
    }

    m_x = x;
    fftwf_execute(m_fftPlan);
    y = m_y;
}

void FftCalculator::ifft(arma::cx_fvec& x, arma::cx_fvec& y)
{
    if (x.n_elem != m_x.n_elem)
    {
        THROW_INVALID_VALUE_EXCEPTION("X is not compatible with the constructor size", "");
    }

    m_x = x;
    fftwf_execute(m_ifftPlan);
    y = m_y / m_y.n_elem;
}
