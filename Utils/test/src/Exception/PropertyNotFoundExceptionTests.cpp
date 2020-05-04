#include <Utils/Exception/PropertyNotFoundException.h>

#include <gtest/gtest.h>

using namespace adaptone;
using namespace std;

TEST(PropertyNotFoundExceptionTests, constructor_shouldSetTheRightMessage)
{
    try
    {
        THROW_PROPERTY_NOT_FOUND_EXCEPTION("my_key");
    }
    catch (exception& ex)
    {
        string message = ex.what();
        EXPECT_NE(message.find("PropertyNotFoundExceptionTests.cpp"), string::npos);
        EXPECT_NE(message.find("constructor_shouldSetTheRightMessage"), string::npos);
        EXPECT_NE(message.find("12"), string::npos);
        EXPECT_NE(message.find("PropertyNotFoundException:"), string::npos);
        EXPECT_NE(message.find("key=my_key"), string::npos);
    }
}
