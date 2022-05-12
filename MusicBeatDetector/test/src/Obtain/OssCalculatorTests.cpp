#include <MusicBeatDetector/Obtain/OssCalculator.h>

#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(OssCalculatorTests, constructor_invalidParameter_shouldThrowNotSupportedException)
{
    EXPECT_THROW(OssCalculator(128, 64, 15), NotSupportedException);
    EXPECT_THROW(OssCalculator(127, 156, 15), NotSupportedException);
}

TEST(OssCalculatorTests, generate_invalidFrameSampleCount_shouldReturnOss)
{
    constexpr size_t FrameSampleCount = 10;
    PcmAudioFrame frame(PcmAudioFrameFormat::Float, 1, FrameSampleCount + 1);
    OssCalculator ossCalculator(FrameSampleCount, 2 * FrameSampleCount);

    EXPECT_THROW(ossCalculator.calculate(frame), NotSupportedException);
}

TEST(OssCalculatorTests, calculate_shouldReturnOss)
{
    constexpr size_t FrameSampleCount = 10;
    float frameData1[FrameSampleCount] = {1, 2, 3, 4, 3, 2, 1, 10, 1, 5};
    float frameData2[FrameSampleCount] = {5, 4, 3, 2, 1, 2, 3, 4, 5, 6};
    PcmAudioFrame frame1(PcmAudioFrameFormat::Float, 1, FrameSampleCount, reinterpret_cast<uint8_t*>(frameData1));
    PcmAudioFrame frame2(PcmAudioFrameFormat::Float, 1, FrameSampleCount, reinterpret_cast<uint8_t*>(frameData2));

    OssCalculator ossCalculator(FrameSampleCount, 2 * FrameSampleCount);
    EXPECT_FLOAT_EQ(ossCalculator.calculate(frame1), 0.32191199);
    EXPECT_FLOAT_EQ(ossCalculator.calculate(frame2), 0.96134341);
}
