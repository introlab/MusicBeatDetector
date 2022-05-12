#include <MusicBeatDetector/Utils/Exception/PropertyParseException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(PropertyParseExceptionTests, constructor_shouldSetTheRightMessage)
{
    try
    {
        THROW_PROPERTY_PARSE_EXCEPTION("my_key", "my_value");
    }
    catch (exception& ex)
    {
        string message = ex.what();
        EXPECT_NE(message.find("PropertyParseExceptionTests.cpp"), string::npos);
        EXPECT_NE(message.find("constructor_shouldSetTheRightMessage"), string::npos);
        EXPECT_NE(message.find("12"), string::npos);
        EXPECT_NE(message.find("PropertyParseException:"), string::npos);
        EXPECT_NE(message.find("key=my_key"), string::npos);
        EXPECT_NE(message.find("value=my_value"), string::npos);
    }
}
