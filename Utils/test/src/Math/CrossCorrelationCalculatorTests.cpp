#include <Utils/Math/CrossCorrelationCalculator.h>

#include <Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(CrossCorrelationCalculatorTests, circularCrossCorrelation_invalidSize_shouldThrowNotSupportedException)
{
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

TEST(CrossCorrelationCalculatorTests, crossCorrelation_shouldReturnTheCrossCorrelation)
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
