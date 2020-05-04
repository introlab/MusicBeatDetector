#include <Utils/Data/ArrayToPcmConverter.h>

#include <gtest/gtest.h>

using namespace adaptone;
using namespace std;

TEST(ArrayToPcmConverterTests, convertSigned8_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 4;
    constexpr size_t ChannelCount = 2;
    double input[FrameSampleCount * ChannelCount];
    int8_t output[FrameSampleCount * ChannelCount];

    input[0] = -1.0;
    input[1] = 1.0;
    input[2] = -0.5;
    input[3] = -1.1;

    input[4] = 0.0;
    input[5] = 0.5;
    input[6] = 0.25;
    input[7] = 1.1;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Signed8);

    EXPECT_EQ(output[0], -128);
    EXPECT_EQ(output[1], 0);
    EXPECT_EQ(output[2], 127);
    EXPECT_EQ(output[3], 64);
    EXPECT_EQ(output[4], -64);
    EXPECT_EQ(output[5], 32);
    EXPECT_EQ(output[6], -128);
    EXPECT_EQ(output[7], 127);
}

TEST(ArrayToPcmConverterTests, convertSigned16_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 4;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    int16_t output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;
    input[3] = -1.1;

    input[4] = 0;
    input[5] = 0.5;
    input[6] = 0.25;
    input[7] = 1.1;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Signed16);

    EXPECT_EQ(output[0], -32768);
    EXPECT_EQ(output[1], 0);
    EXPECT_EQ(output[2], 32767);
    EXPECT_EQ(output[3], 16384);
    EXPECT_EQ(output[4], -16384);
    EXPECT_EQ(output[5], 8192);
    EXPECT_EQ(output[6], -32768);
    EXPECT_EQ(output[7], 32767);
}

TEST(ArrayToPcmConverterTests, convertSigned24_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    uint8_t output[3 * FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Signed24);

    EXPECT_EQ(output[0], 0x00);
    EXPECT_EQ(output[1], 0x00);
    EXPECT_EQ(output[2], 0x80);

    EXPECT_EQ(output[3], 0x00);
    EXPECT_EQ(output[4], 0x00);
    EXPECT_EQ(output[5], 0x00);

    EXPECT_EQ(output[6], 0xff);
    EXPECT_EQ(output[7], 0xff);
    EXPECT_EQ(output[8], 0x7f);

    EXPECT_EQ(output[9], 0x00);
    EXPECT_EQ(output[10], 0x00);
    EXPECT_EQ(output[11], 0x40);

    EXPECT_EQ(output[12], 0x00);
    EXPECT_EQ(output[13], 0x00);
    EXPECT_EQ(output[14], 0xc0);

    EXPECT_EQ(output[15], 0x00);
    EXPECT_EQ(output[16], 0x00);
    EXPECT_EQ(output[17], 0x20);
}

TEST(ArrayToPcmConverterTests, convertSignedPadded24_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    int32_t output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::SignedPadded24);

    EXPECT_EQ(output[0], -8388608);
    EXPECT_EQ(output[1], 0);
    EXPECT_EQ(output[2], 8388607);
    EXPECT_EQ(output[3], 4194304);
    EXPECT_EQ(output[4], -4194304);
    EXPECT_EQ(output[5], 2097152);
}

TEST(ArrayToPcmConverterTests, convertSigned32_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    int32_t output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Signed32);

    EXPECT_EQ(output[0], -2147483648);
    EXPECT_EQ(output[1], 0);
    EXPECT_EQ(output[2], 2147483647);
    EXPECT_EQ(output[3], 1073741824);
    EXPECT_EQ(output[4], -1073741824);
    EXPECT_EQ(output[5], 536870912);
}

TEST(ArrayToPcmConverterTests, convertUnsigned8_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    uint8_t output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned8);

    EXPECT_EQ(output[0], 0);
    EXPECT_EQ(output[1], 128);
    EXPECT_EQ(output[2], 255);
    EXPECT_EQ(output[3], 191);
    EXPECT_EQ(output[4], 64);
    EXPECT_EQ(output[5], 159);
}

TEST(ArrayToPcmConverterTests, convertUnsigned16_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    uint16_t output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned16);

    EXPECT_EQ(output[0], 0);
    EXPECT_EQ(output[1], 32768);
    EXPECT_EQ(output[2], 65535);
    EXPECT_EQ(output[3], 49151);
    EXPECT_EQ(output[4], 16384);
    EXPECT_EQ(output[5], 40959);
}

TEST(ArrayToPcmConverterTests, convertUnsigned24_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    uint8_t output[3 * FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned24);

    EXPECT_EQ(output[0], 0x00);
    EXPECT_EQ(output[1], 0x00);
    EXPECT_EQ(output[2], 0x00);

    EXPECT_EQ(output[3], 0x00);
    EXPECT_EQ(output[4], 0x00);
    EXPECT_EQ(output[5], 0x80);

    EXPECT_EQ(output[6], 0xff);
    EXPECT_EQ(output[7], 0xff);
    EXPECT_EQ(output[8], 0xff);

    EXPECT_EQ(output[9], 0xff);
    EXPECT_EQ(output[10], 0xff);
    EXPECT_EQ(output[11], 0xbf);

    EXPECT_EQ(output[12], 0x00);
    EXPECT_EQ(output[13], 0x00);
    EXPECT_EQ(output[14], 0x40);

    EXPECT_EQ(output[15], 0xff);
    EXPECT_EQ(output[16], 0xff);
    EXPECT_EQ(output[17], 0x9f);
}

TEST(ArrayToPcmConverterTests, convertUnsignedPadded24_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    uint32_t output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::UnsignedPadded24);

    EXPECT_EQ(output[0], 0);
    EXPECT_EQ(output[1], 8388608);
    EXPECT_EQ(output[2], 16777215);
    EXPECT_EQ(output[3], 12582911);
    EXPECT_EQ(output[4], 4194304);
    EXPECT_EQ(output[5], 10485759);
}

TEST(ArrayToPcmConverterTests, convertUnsigned32_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    uint32_t output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned32);

    EXPECT_EQ(output[0], 0);
    EXPECT_EQ(output[1], 2147483648);
    EXPECT_EQ(output[2], 4294967295);
    EXPECT_EQ(output[3], 3221225472);
    EXPECT_EQ(output[4], 1073741824);
    EXPECT_EQ(output[5], 2684354560);
}

TEST(ArrayToPcmConverterTests, convertFloat_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Float);

    EXPECT_EQ(output[0], -1);
    EXPECT_EQ(output[1], 0);
    EXPECT_EQ(output[2], 1);
    EXPECT_EQ(output[3], 0.5);
    EXPECT_EQ(output[4], -0.5);
    EXPECT_EQ(output[5], 0.25);
}

TEST(ArrayToPcmConverterTests, convertDouble_shouldConvertTheDataFromFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    double output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 1;
    input[2] = -0.5;

    input[3] = 0;
    input[4] = 0.5;
    input[5] = 0.25;

    ArrayToPcmConverter::convertArrayToPcm(input, reinterpret_cast<uint8_t*>(output), FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Double);

    EXPECT_EQ(output[0], -1);
    EXPECT_EQ(output[1], 0);
    EXPECT_EQ(output[2], 1);
    EXPECT_EQ(output[3], 0.5);
    EXPECT_EQ(output[4], -0.5);
    EXPECT_EQ(output[5], 0.25);
}
