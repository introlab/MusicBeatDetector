#include <Utils/Data/PcmToArrayConverter.h>

#include <gtest/gtest.h>

using namespace adaptone;
using namespace std;

static constexpr double MaxAbsError = 0.01;

TEST(PcmToArrayConverterTests, convertSigned8_shouldConvertTheDataToFloatingPointArray)
{
    constexpr size_t FrameSampleCount = 3;
    constexpr size_t ChannelCount = 2;
    int8_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = -128;
    input[1] = 0;
    input[2] = 127;
    input[3] = 64;
    input[4] = -64;
    input[5] = 32;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Signed8);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertSigned16_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    int16_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = -32768;
    input[1] = 0;
    input[2] = 32767;
    input[3] = 16384;
    input[4] = -16384;
    input[5] = 8192;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Signed16);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertSigned24_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    uint8_t input[3 * FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    //-8388608
    input[0] = 0x00;
    input[1] = 0x00;
    input[2] = 0x80;

    //0
    input[3] = 0x00;
    input[4] = 0x00;
    input[5] = 0x00;

    //8388607
    input[6] = 0xff;
    input[7] = 0xff;
    input[8] = 0x7f;

    //4194304
    input[9] = 0x00;
    input[10] = 0x00;
    input[11] = 0x40;

    //-4194304
    input[12] = 0x00;
    input[13] = 0x00;
    input[14] = 0xC0;

    //2097152
    input[15] = 0x00;
    input[16] = 0x00;
    input[17] = 0x20;

    PcmToArrayConverter::convertPcmToArray(input, output, FrameSampleCount, ChannelCount, PcmAudioFrameFormat::Signed24);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertSignedPadded24_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    int32_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = -8388608;
    input[1] = 0;
    input[2] = 8388607;
    input[3] = 4194304;
    input[4] = -4194304;
    input[5] = 2097152;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::SignedPadded24);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertSigned32_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    int32_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = -2147483648;
    input[1] = 0;
    input[2] = 2147483647;
    input[3] = 1073741824;
    input[4] = -1073741824;
    input[5] = 536870912;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Signed32);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertUnsigned8_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    uint8_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = 0;
    input[1] = 128;
    input[2] = 255;
    input[3] = 192;
    input[4] = 64;
    input[5] = 160;

    PcmToArrayConverter::convertPcmToArray(input, output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned8);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertUnsigned16_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    uint16_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = 0;
    input[1] = 32768;
    input[2] = 65535;
    input[3] = 49152;
    input[4] = 16384;
    input[5] = 40960;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned16);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertUnsigned24_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    uint8_t input[3 * FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    //0
    input[0] = 0x00;
    input[1] = 0x00;
    input[2] = 0x00;

    //8388608
    input[3] = 0x00;
    input[4] = 0x00;
    input[5] = 0x80;

    //16777215
    input[6] = 0xff;
    input[7] = 0xff;
    input[8] = 0xff;

    //12582912
    input[9] = 0x00;
    input[10] = 0x00;
    input[11] = 0xc0;

    //4194304
    input[12] = 0x00;
    input[13] = 0x00;
    input[14] = 0x40;

    //10485760
    input[15] = 0x00;
    input[16] = 0x00;
    input[17] = 0xa0;

    PcmToArrayConverter::convertPcmToArray(input, output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned24);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertUnsignedPadded24_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    uint32_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = 0;
    input[1] = 8388608;
    input[2] = 16777215;
    input[3] = 12582912;
    input[4] = 4194304;
    input[5] = 10485760;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::UnsignedPadded24);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertUnsigned32_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    uint32_t input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = 0;
    input[1] = 2147483648;
    input[2] = 4294967295;
    input[3] = 3221225472;
    input[4] = 1073741824;
    input[5] = 2684354560;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Unsigned32);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertFloat_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    float input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 0;
    input[2] = 1;
    input[3] = 0.5;
    input[4] = -0.5;
    input[5] = 0.25;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Float);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}

TEST(PcmToArrayConverterTests, convertDouble_shouldConvertTheDataToFloatingPointArray)
{
    size_t FrameSampleCount = 3;
    size_t ChannelCount = 2;
    double input[FrameSampleCount * ChannelCount];
    float output[FrameSampleCount * ChannelCount];

    input[0] = -1;
    input[1] = 0;
    input[2] = 1;
    input[3] = 0.5;
    input[4] = -0.5;
    input[5] = 0.25;

    PcmToArrayConverter::convertPcmToArray(reinterpret_cast<uint8_t*>(input), output, FrameSampleCount, ChannelCount,
        PcmAudioFrameFormat::Double);

    EXPECT_NEAR(output[0], -1, MaxAbsError);
    EXPECT_NEAR(output[1], 1, MaxAbsError);
    EXPECT_NEAR(output[2], -0.5, MaxAbsError);

    EXPECT_NEAR(output[3], 0, MaxAbsError);
    EXPECT_NEAR(output[4], 0.5, MaxAbsError);
    EXPECT_NEAR(output[5], 0.25, MaxAbsError);
}
