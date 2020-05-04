#include <Utils/Data/PcmAudioFrameFormat.h>

#include <Utils/Exception/InvalidValueException.h>

#include <gtest/gtest.h>

#include <sstream>
#include <chrono>

using namespace adaptone;
using namespace std;

TEST(PcmAudioFrameFormatTests, parseFormat_shouldReturnTheRightFormat)
{
    EXPECT_EQ(parseFormat("signed_8"), PcmAudioFrameFormat::Signed8);
    EXPECT_EQ(parseFormat("signed_16"), PcmAudioFrameFormat::Signed16);
    EXPECT_EQ(parseFormat("signed_24"), PcmAudioFrameFormat::Signed24);
    EXPECT_EQ(parseFormat("signed_padded_24"), PcmAudioFrameFormat::SignedPadded24);
    EXPECT_EQ(parseFormat("signed_32"), PcmAudioFrameFormat::Signed32);

    EXPECT_EQ(parseFormat("unsigned_8"), PcmAudioFrameFormat::Unsigned8);
    EXPECT_EQ(parseFormat("unsigned_16"), PcmAudioFrameFormat::Unsigned16);
    EXPECT_EQ(parseFormat("unsigned_24"), PcmAudioFrameFormat::Unsigned24);
    EXPECT_EQ(parseFormat("unsigned_padded_24"), PcmAudioFrameFormat::UnsignedPadded24);
    EXPECT_EQ(parseFormat("unsigned_32"), PcmAudioFrameFormat::Unsigned32);

    EXPECT_EQ(parseFormat("float"), PcmAudioFrameFormat::Float);
    EXPECT_EQ(parseFormat("double"), PcmAudioFrameFormat::Double);

    EXPECT_THROW(parseFormat("unsigned_32asdasd"), InvalidValueException);
}

TEST(PcmAudioFrameFormatTests, formatSize_shouldReturnTheRightSize)
{
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Signed8), 1);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Signed16), 2);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Signed24), 3);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::SignedPadded24), 4);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Signed32), 4);

    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Unsigned8), 1);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Unsigned16), 2);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Unsigned24), 3);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::UnsignedPadded24), 4);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Unsigned32), 4);

    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Float), 4);
    EXPECT_EQ(formatSize(PcmAudioFrameFormat::Double), 8);
}

TEST(PcmAudioFrameFormatTests, size_shouldReturnTheFrameSize)
{
    EXPECT_EQ(size(PcmAudioFrameFormat::Signed16, 2, 3), 12);
}
