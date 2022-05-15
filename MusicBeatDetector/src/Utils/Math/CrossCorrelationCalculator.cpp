#include <MusicBeatDetector/Utils/Math/CrossCorrelationCalculator.h>

#include <MusicBeatDetector/Utils/Math/Math.h>
#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>

using namespace introlab;
using namespace std;

CircularCrossCorrelationCalculator::CircularCrossCorrelationCalculator(size_t size)
{
    if (size == 0)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("The size must be greater than 0.");
    }

    m_a.zeros(size);
    m_A.zeros(size / 2 + 1);
    m_b.zeros(size);
    m_B.zeros(m_A.n_elem);
    m_c.zeros(size);
    m_C.zeros(m_A.n_elem);

    m_fftPlanA = fftwf_plan_dft_r2c_1d(
        static_cast<int>(size),
        m_a.memptr(),
        reinterpret_cast<fftwf_complex*>(m_A.memptr()),
        FFTW_PATIENT);
    m_fftPlanB = fftwf_plan_dft_r2c_1d(
        static_cast<int>(size),
        m_b.memptr(),
        reinterpret_cast<fftwf_complex*>(m_B.memptr()),
        FFTW_PATIENT);

    m_ifftPlan = fftwf_plan_dft_c2r_1d(
        static_cast<int>(size),
        reinterpret_cast<fftwf_complex*>(m_C.memptr()),
        m_c.memptr(),
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

    m_a = a;
    m_b = b;

    return calculate();
}

arma::fvec CircularCrossCorrelationCalculator::calculate()
{
    fftwf_execute(m_fftPlanA);
    fftwf_execute(m_fftPlanB);

    m_C = m_A % arma::conj(m_B);
    fftwf_execute(m_ifftPlan);
    m_c /= static_cast<float>(m_c.n_elem);

    return fftShift(m_c);
}

CrossCorrelationCalculator::CrossCorrelationCalculator(size_t size)
    : m_size(size),
      m_circularCrossCorrelationSize(nextPower(2 * size - 1, static_cast<size_t>(2))),
      m_circularCrossCorrelationCalculator(m_circularCrossCorrelationSize)
{
}

CrossCorrelationCalculator::~CrossCorrelationCalculator() {}

arma::fvec CrossCorrelationCalculator::calculate(const arma::fvec& a, const arma::fvec& b)
{
    constexpr size_t MaxTemporalSize = 31;

    if (a.n_elem != m_size || b.n_elem != m_size)
    {
        THROW_NOT_SUPPORTED_EXCEPTION("a and b size must be equal to the size specified in the constructor");
    }
    if (m_size <= MaxTemporalSize)
    {
        return arma::conv(a, arma::reverse(b));
    }

    size_t resultSize = 2 * m_size - 1;
    size_t offset = (m_circularCrossCorrelationSize - resultSize) / 2 + 1;

    m_circularCrossCorrelationCalculator.m_a(arma::span(0, m_size - 1)) = a;
    m_circularCrossCorrelationCalculator.m_b(arma::span(0, m_size - 1)) = b;
    return m_circularCrossCorrelationCalculator.calculate()(arma::span(offset, offset + resultSize - 1));
}
