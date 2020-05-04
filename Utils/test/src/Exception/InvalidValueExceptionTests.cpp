#include <Utils/Exception/InvalidValueException.h>

#include <gtest/gtest.h>

using namespace adaptone;
using namespace std;

TEST(InvalidValueExceptionTests, constructor_shouldSetTheRightMessage)
{
    try
    {
        THROW_INVALID_VALUE_EXCEPTION("my_key", "my_value");
    }
    catch (exception& ex)
    {
        string message = ex.what();
        EXPECT_NE(message.find("InvalidValueExceptionTests.cpp"), string::npos);
        EXPECT_NE(message.find("constructor_shouldSetTheRightMessage"), string::npos);
        EXPECT_NE(message.find("12"), string::npos);
        EXPECT_NE(message.find("InvalidValueException:"), string::npos);
        EXPECT_NE(message.find("key=my_key"), string::npos);
        EXPECT_NE(message.find("value=my_value"), string::npos);
    }
}
