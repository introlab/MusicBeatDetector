#include <MusicBeatDetector/Utils/Math/CrossCorrelationCalculator.h>

#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(CrossCorrelationCalculatorTests, nextPower_shouldReturnTheRightValues)
{
    EXPECT_EQ(nextPower(0, 2), 0);
    EXPECT_EQ(nextPower(1, 2), 1);
    EXPECT_EQ(nextPower(2, 2), 2);
    EXPECT_EQ(nextPower(3, 2), 4);
    EXPECT_EQ(nextPower(5, 2), 8);
    EXPECT_EQ(nextPower(510, 2), 512);
    EXPECT_EQ(nextPower(2047, 2), 2048);

    EXPECT_EQ(nextPower(8, 3), 9);
}

TEST(CrossCorrelationCalculatorTests, circularCrossCorrelation_invalidSize_shouldThrowNotSupportedException)
{
    EXPECT_THROW(CircularCrossCorrelationCalculator(0), NotSupportedException);

    arma::fvec a({1, 2, 3, -1, 0, 0, 0});
    arma::fvec b({1, -1, 1, -1, 0, 0, 0, 0});

    CircularCrossCorrelationCalculator calculator(b.n_elem);

    EXPECT_THROW(calculator.calculate(a, b), NotSupportedException);
    EXPECT_THROW(calculator.calculate(b, a), NotSupportedException);
}

TEST(CrossCorrelationCalculatorTests, circularCrossCorrelation_shouldReturnTheCircularCrossCorrelation)
{
    arma::fvec a({1, 2, 3, -1, 0, 0, 0});
    arma::fvec b({1, -1, 1, -1, 0, 0, 0});

    CircularCrossCorrelationCalculator calculator(a.n_elem);

    arma::fvec c = calculator.calculate(a, b);

    EXPECT_FLOAT_EQ(c(0), -1);
    EXPECT_FLOAT_EQ(c(1), -1);
    EXPECT_FLOAT_EQ(c(2), -2);
    EXPECT_FLOAT_EQ(c(3), 3);
    EXPECT_FLOAT_EQ(c(4), -2);
    EXPECT_FLOAT_EQ(c(5), 4);
    EXPECT_FLOAT_EQ(c(6), -1);
}

TEST(CrossCorrelationCalculatorTests, crossCorrelation_invalidSize_shouldThrowNotSupportedException)
{
    arma::fvec a({1, 2, 3, -1, 0, 0, 0});
    arma::fvec b({1, -1, 1, -1, 0, 0, 0, 0});

    CrossCorrelationCalculator calculator(b.n_elem);

    EXPECT_THROW(calculator.calculate(a, b), NotSupportedException);
    EXPECT_THROW(calculator.calculate(b, a), NotSupportedException);
}

TEST(CrossCorrelationCalculatorTests, crossCorrelation_temporal_shouldReturnTheCrossCorrelation)
{
    arma::fvec a({1, 2, 3});
    arma::fvec b({1, -1, 1});

    CrossCorrelationCalculator calculator(b.n_elem);
    arma::fvec c = calculator.calculate(a, b);

    EXPECT_FLOAT_EQ(c(0), 1);
    EXPECT_FLOAT_EQ(c(1), 1);
    EXPECT_FLOAT_EQ(c(2), 2);
    EXPECT_FLOAT_EQ(c(3), -1);
    EXPECT_FLOAT_EQ(c(4), 3);
}

class CrossCorrelationCalculatorTestsP : public ::testing::TestWithParam<size_t>
{
};

TEST_P(CrossCorrelationCalculatorTestsP, crossCorrelation_frequency_shouldReturnTheCrossCorrelation)
{
    constexpr float AbsError = 0.01;

    size_t size = GetParam();
    arma::fvec a = arma::regspace<arma::fvec>(0, static_cast<float>(size) - 1);
    arma::fvec b = arma::regspace<arma::fvec>(-5, static_cast<float>(size) - 6);
    ASSERT_EQ(a.n_elem, size);
    ASSERT_EQ(a.n_elem, b.n_elem);

    CrossCorrelationCalculator calculator(b.n_elem);
    arma::fvec c = calculator.calculate(a, b);
    arma::fvec expectedC = arma::conv(a, arma::reverse(b));

    for (size_t i = 0; i < a.n_elem; i++)
    {
        EXPECT_NEAR(c(i), expectedC(i), AbsError);
    }
}

INSTANTIATE_TEST_CASE_P(
    CrossCorrelationCalculatorTests,
    CrossCorrelationCalculatorTestsP,
    ::testing::Values(32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52));
