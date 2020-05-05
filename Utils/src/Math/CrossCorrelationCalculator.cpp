#include <Utils/Math/CrossCorrelationCalculator.h>

#include <Utils/Math/Math.h>
#include <Utils/Exception/NotSupportedException.h>

using namespace introlab;
using namespace std;

CircularCrossCorrelationCalculator::CircularCrossCorrelationCalculator(size_t size)
{
    m_a = arma::zeros<arma::cx_fvec>(size);
    m_A = arma::zeros<arma::cx_fvec>(size);
    m_b = arma::zeros<arma::cx_fvec>(size);
    m_B = arma::zeros<arma::cx_fvec>(size);
    m_c = arma::zeros<arma::cx_fvec>(size);
    m_C = arma::zeros<arma::cx_fvec>(size);

    m_fftPlanA = fftwf_plan_dft_1d(m_a.n_elem,
        reinterpret_cast<fftwf_complex*>(m_a.memptr()),
        reinterpret_cast<fftwf_complex*>(m_A.memptr()),
        FFTW_FORWARD,
        FFTW_PATIENT);

    m_fftPlanB = fftwf_plan_dft_1d(m_b.n_elem,
        reinterpret_cast<fftwf_complex*>(m_b.memptr()),
        reinterpret_cast<fftwf_complex*>(m_B.memptr()),
        FFTW_FORWARD,
        FFTW_PATIENT);

    m_ifftPlan = fftwf_plan_dft_1d(m_c.n_elem,
        reinterpret_cast<fftwf_complex*>(m_C.memptr()),
        reinterpret_cast<fftwf_complex*>(m_c.memptr()),
        FFTW_BACKWARD,
        FFTW_PATIENT);
}

CircularCrossCorrelationCalculator::~CircularCrossCorrelationCalculator()
{
    fftwf_destroy_plan(m_fftPlanA);
    fftwf_destroy_plan(m_fftPlanB);
    fftwf_destroy_plan(m_ifftPlan);
}

arma::fvec CircularCrossCorrelationCalculator::calculate(const arma::fvec& a, const arma::fvec& b)
{
    if (m_a.n_elem != a.n_elem || m_b.n_elem != b.n_elem)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("a and b size must be equal to the size specified in the constructor");
    }

    m_a(arma::span(0, m_a.n_elem - 1)) = arma::conv_to<arma::cx_fvec>::from(a);
    m_b(arma::span(0, m_b.n_elem - 1)) = arma::conv_to<arma::cx_fvec>::from(b);

    fftwf_execute(m_fftPlanA);
    fftwf_execute(m_fftPlanB);

    m_C = m_A % arma::conj(m_B);
    fftwf_execute(m_ifftPlan);
    m_c /= m_c.n_elem;

    return fftShift(arma::real(m_c));
}

CrossCorrelationCalculator::CrossCorrelationCalculator(size_t size) :
    m_size(size),
    m_circularCrossCorrelationCalculator(2 * size - 1)
{
    m_a = arma::zeros<arma::fvec>(2 * size - 1);
    m_b = arma::zeros<arma::fvec>(2 * size - 1);
}

CrossCorrelationCalculator::~CrossCorrelationCalculator()
{
}

arma::fvec CrossCorrelationCalculator::calculate(const arma::fvec& a, const arma::fvec& b)
{
    constexpr size_t MAX_TEMPORAL_SIZE = 1024;

    if (a.n_elem != m_size || b.n_elem != m_size)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("a and b size must be equal to the size specified in the constructor");
    }
    if (m_size <= MAX_TEMPORAL_SIZE)
    {
        return arma::conv(a, arma::reverse(b));
    }

    m_a(arma::span(0, m_size - 1)) = a;
    m_b(arma::span(0, m_size - 1)) = b;

    return m_circularCrossCorrelationCalculator.calculate(m_a, m_b);
}
