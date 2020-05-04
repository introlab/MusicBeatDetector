#include <Utils/Exception/LoggedException.h>

#include <gtest/gtest.h>

using namespace adaptone;
using namespace std;

TEST(LoggedExceptionTests, constructor_shouldSetTheRightMessage)
{
    try
    {
        THROW_LOGGED_EXCEPTION("my message");
    }
    catch (exception& ex)
    {
        string message = ex.what();
        EXPECT_NE(message.find("LoggedExceptionTests.cpp"), string::npos);
        EXPECT_NE(message.find("constructor_shouldSetTheRightMessage"), string::npos);
        EXPECT_NE(message.find("12"), string::npos);
        EXPECT_NE(message.find("my message"), string::npos);
    }
}
