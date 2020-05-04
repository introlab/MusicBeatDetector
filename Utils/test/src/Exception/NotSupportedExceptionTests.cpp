#include <Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace adaptone;
using namespace std;

TEST(NotSupportedExceptionTests, constructor_shouldSetTheRightMessage)
{
    try
    {
        THROW_NOT_SUPPORTED_EXCEPTION("my message");
    }
    catch (exception& ex)
    {
        string message = ex.what();
        EXPECT_NE(message.find("NotSupportedExceptionTests.cpp"), string::npos);
        EXPECT_NE(message.find("constructor_shouldSetTheRightMessage"), string::npos);
        EXPECT_NE(message.find("12"), string::npos);
        EXPECT_NE(message.find("NotSupportedException:"), string::npos);
        EXPECT_NE(message.find("my message"), string::npos);
    }
}
