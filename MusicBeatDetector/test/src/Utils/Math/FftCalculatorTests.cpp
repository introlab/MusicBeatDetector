#include <MusicBeatDetector/Utils/Math/FftCalculator.h>

#include <MusicBeatDetector/Utils/Exception/InvalidValueException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(FftCalculatorTests, fft_wrongSize_shouldThrowInvalidValueException)
{
    arma::cx_fvec x = arma::conv_to<arma::cx_fvec>::from(arma::fvec({2, 2, 2, 2}));
    arma::cx_fvec y = arma::zeros<arma::cx_fvec>(x.n_elem);

    FftCalculator testee(x.n_elem + 1);
    EXPECT_THROW(testee.fft(x, y), InvalidValueException);
}

TEST(FftCalculatorTests, fft_preallocatedMemory_shouldReturnTheFft)
{
    arma::cx_fvec x = arma::conv_to<arma::cx_fvec>::from(arma::fvec({2, 2, 2, 2}));
    arma::cx_fvec y = arma::zeros<arma::cx_fvec>(x.n_elem);

    FftCalculator testee(x.n_elem);
    testee.fft(x, y);

    EXPECT_EQ(y(0), complex<float>(8, 0));
    EXPECT_EQ(y(1), complex<float>(0, 0));
    EXPECT_EQ(y(2), complex<float>(0, 0));
    EXPECT_EQ(y(3), complex<float>(0, 0));
}

TEST(FftCalculatorTests, fft_shouldReturnTheFft)
{
    arma::cx_fvec x = arma::conv_to<arma::cx_fvec>::from(arma::fvec({1, 1, 1}));
    arma::cx_fvec y;

    FftCalculator testee(x.n_elem);
    testee.fft(x, y);

    EXPECT_EQ(y(0), complex<float>(3, 0));
    EXPECT_EQ(y(1), complex<float>(0, 0));
    EXPECT_EQ(y(2), complex<float>(0, 0));
}

TEST(FftCalculatorTests, ifft_wrongSize_shouldThrowInvalidValueException)
{
    arma::cx_fvec x = arma::conv_to<arma::cx_fvec>::from(arma::fvec({2, 2, 2, 2}));
    arma::cx_fvec y = arma::zeros<arma::cx_fvec>(x.n_elem);

    FftCalculator testee(x.n_elem + 1);
    EXPECT_THROW(testee.ifft(x, y), InvalidValueException);
}

TEST(FftCalculatorTests, ifft_preallocatedMemory_shouldReturnTheIfft)
{
    arma::cx_fvec x({complex<float>(8, 0), complex<float>(0, 0), complex<float>(0, 0), complex<float>(0, 0)});
    arma::cx_fvec y = arma::zeros<arma::cx_fvec>(x.n_elem);

    FftCalculator testee(x.n_elem);
    testee.ifft(x, y);

    EXPECT_EQ(y(0), complex<float>(2, 0));
    EXPECT_EQ(y(1), complex<float>(2, 0));
    EXPECT_EQ(y(2), complex<float>(2, 0));
    EXPECT_EQ(y(3), complex<float>(2, 0));
}

TEST(FftCalculatorTests, ifft_shouldReturnTheIfft)
{
    arma::cx_fvec x({complex<float>(3, 0), complex<float>(0, 0), complex<float>(0, 0)});
    arma::cx_fvec y;

    FftCalculator testee(x.n_elem);
    testee.ifft(x, y);

    EXPECT_EQ(y(0), complex<float>(1, 0));
    EXPECT_EQ(y(1), complex<float>(1, 0));
    EXPECT_EQ(y(2), complex<float>(1, 0));
}
