#include <Utils/Math/Math.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(MathTests, hamming_shouldReturnTheHammingWindow)
{
    constexpr size_t WindowLength = 5;
    arma::fvec window = hamming<arma::fvec>(WindowLength);

    EXPECT_EQ(window.n_elem, WindowLength);
    EXPECT_FLOAT_EQ(window(0), 0.08);
    EXPECT_FLOAT_EQ(window(1), 0.54);
    EXPECT_FLOAT_EQ(window(2), 1);
    EXPECT_FLOAT_EQ(window(3), 0.540000);
    EXPECT_FLOAT_EQ(window(4), 0.08);
}

TEST(MathTests, fft_preallocatedMemory_shouldReturnTheFft)
{
    arma::cx_fvec x = arma::conv_to<arma::cx_fvec>::from(arma::fvec({ 2, 2, 2, 2 }));
    arma::cx_fvec y = arma::zeros<arma::cx_fvec>(x.n_elem);

    fft(x, y);

    EXPECT_EQ(y(0), complex<float>(8, 0));
    EXPECT_EQ(y(1), complex<float>(0, 0));
    EXPECT_EQ(y(2), complex<float>(0, 0));
    EXPECT_EQ(y(3), complex<float>(0, 0));
}

TEST(MathTests, fft_shouldReturnTheFft)
{
    arma::cx_fvec x = arma::conv_to<arma::cx_fvec>::from(arma::fvec({ 1, 1, 1 }));
    arma::cx_fvec y;

    fft(x, y);

    EXPECT_EQ(y(0), complex<float>(3, 0));
    EXPECT_EQ(y(1), complex<float>(0, 0));
    EXPECT_EQ(y(2), complex<float>(0, 0));
}

TEST(MathTests, ifft_preallocatedMemory_shouldReturnTheIfft)
{
    arma::cx_fvec x({ complex<float>(8, 0), complex<float>(0, 0), complex<float>(0, 0), complex<float>(0, 0) });
    arma::cx_fvec y = arma::zeros<arma::cx_fvec>(x.n_elem);

    ifft(x, y);

    EXPECT_EQ(y(0), complex<float>(2, 0));
    EXPECT_EQ(y(1), complex<float>(2, 0));
    EXPECT_EQ(y(2), complex<float>(2, 0));
    EXPECT_EQ(y(3), complex<float>(2, 0));
}

TEST(MathTests, ifft_shouldReturnTheIfft)
{
    arma::cx_fvec x({ complex<float>(3, 0), complex<float>(0, 0), complex<float>(0, 0) });
    arma::cx_fvec y;

    ifft(x, y);

    EXPECT_EQ(y(0), complex<float>(1, 0));
    EXPECT_EQ(y(1), complex<float>(1, 0));
    EXPECT_EQ(y(2), complex<float>(1, 0));
}

TEST(MathTests, fftShift_even_shouldReturnFttShift)
{
    arma::fvec a({1, 2, 3, 4, 5, 6});
    arma::fvec b = fftShift(a);

    EXPECT_FLOAT_EQ(b(0), 4);
    EXPECT_FLOAT_EQ(b(1), 5);
    EXPECT_FLOAT_EQ(b(2), 6);
    EXPECT_FLOAT_EQ(b(3), 1);
    EXPECT_FLOAT_EQ(b(4), 2);
    EXPECT_FLOAT_EQ(b(5), 3);
}

TEST(MathTests, fftShift_odd_shouldReturnFttShift)
{
    arma::fvec a({1, 2, 3, 4, 5, 6, 7});
    arma::fvec b = fftShift(a);

    EXPECT_FLOAT_EQ(b(0), 5);
    EXPECT_FLOAT_EQ(b(1), 6);
    EXPECT_FLOAT_EQ(b(2), 7);
    EXPECT_FLOAT_EQ(b(3), 1);
    EXPECT_FLOAT_EQ(b(4), 2);
    EXPECT_FLOAT_EQ(b(5), 3);
    EXPECT_FLOAT_EQ(b(6), 4);
}

TEST(MathTests, crossCorrelation_shouldReturnTheCrossCorrelation)
{
    arma::fvec a({1, 2, 3});
    arma::fvec b({1, -1, 1});

    arma::fvec c = crossCorrelation(a, b);

    EXPECT_FLOAT_EQ(c(0), 1);
    EXPECT_FLOAT_EQ(c(1), 1);
    EXPECT_FLOAT_EQ(c(2), 2);
    EXPECT_FLOAT_EQ(c(3), -1);
    EXPECT_FLOAT_EQ(c(4), 3);
}
