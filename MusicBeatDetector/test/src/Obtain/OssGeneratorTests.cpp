#include <MusicBeatDetector/Obtain/OssGenerator.h>

#include <Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(OssGeneratorTests, constructor_invalidParameter_shouldThrowNotSupportedException)
{
    EXPECT_THROW(OssGenerator(128, 64, 15), NotSupportedException);
    EXPECT_THROW(OssGenerator(127, 156, 15), NotSupportedException);
}

TEST(OssGeneratorTests, generate_invalidFrameSampleCount_shouldReturnOss)
{
    constexpr size_t FrameSampleCount = 10;
    PcmAudioFrame frame(PcmAudioFrameFormat::Float, 1, FrameSampleCount + 1);
    OssGenerator ossGenerator(FrameSampleCount, 2 * FrameSampleCount);

    EXPECT_THROW(ossGenerator.generate(frame), NotSupportedException);
}

TEST(OssGeneratorTests, generate_shouldReturnOss)
{
    constexpr size_t FrameSampleCount = 10;
    float frameData1[FrameSampleCount] = {1, 2, 3, 4, 3, 2, 1, 10, 1, 5};
    float frameData2[FrameSampleCount] = {5, 4, 3, 2, 1, 2, 3, 4, 5, 6};
    PcmAudioFrame frame1(PcmAudioFrameFormat::Float, 1, FrameSampleCount, reinterpret_cast<uint8_t*>(frameData1));
    PcmAudioFrame frame2(PcmAudioFrameFormat::Float, 1, FrameSampleCount, reinterpret_cast<uint8_t*>(frameData2));

    OssGenerator ossGenerator(FrameSampleCount, 2 * FrameSampleCount);
    EXPECT_FLOAT_EQ(ossGenerator.generate(frame1), 0.2920454740524292);
    EXPECT_FLOAT_EQ(ossGenerator.generate(frame2), 0.93209505081176758);
}
