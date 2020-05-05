#include <MusicBeatDetector/Obtain/OssCalculator.h>
#include <MusicBeatDetector/Obtain/BpmEstimator.h>
#include <MusicBeatDetector/Obtain/CbssCalculator.h>

#include <Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(CbssGeneratorTests, constructor_invalidMinBpm_shouldThrowNotSupportedException)
{
    constexpr float OssSamplingFrequency = 44100.0 / 128;
    constexpr float MinBpm = 0;

    EXPECT_THROW(CbssCalculator(OssSamplingFrequency, MinBpm), NotSupportedException);
}

TEST(CbssGeneratorTests, calculate_shouldReturneTheNextCbssValue)
{
    constexpr float OssSamplingFrequency = 344.5;
    constexpr size_t OssWindowSize = 4;
    constexpr float MinBpm = 10000;
    constexpr float MaxBpm = 20000;

    constexpr size_t FrameSampleCount = 4;
    float frameData1[FrameSampleCount] = {1, 0, -1, 0};
    float frameData2[FrameSampleCount] = {0, 1, -1, 0};
    PcmAudioFrame frame1(PcmAudioFrameFormat::Float, 1, FrameSampleCount, reinterpret_cast<uint8_t*>(frameData1));
    PcmAudioFrame frame2(PcmAudioFrameFormat::Float, 1, FrameSampleCount, reinterpret_cast<uint8_t*>(frameData2));

    OssCalculator ossCalculator(FrameSampleCount);
    BpmEstimator bpmEstimator(OssSamplingFrequency, OssWindowSize, MinBpm, MaxBpm);
    CbssCalculator cbssCalculator(OssSamplingFrequency, MinBpm);

    float oss1 = ossCalculator.calculate(frame1);
    float oss2 = ossCalculator.calculate(frame2);

    float bpm1 = bpmEstimator.estimateBpm(oss1);
    float bpm2 = bpmEstimator.estimateBpm(oss2);
    float bpm3 = bpmEstimator.estimateBpm(oss1);
    float bpm4 = bpmEstimator.estimateBpm(oss2);

    EXPECT_EQ(cbssCalculator.calculate(bpm1, oss1), 0);
    EXPECT_EQ(cbssCalculator.calculate(bpm2, oss2), 0);
    EXPECT_EQ(cbssCalculator.calculate(bpm3, oss1), 0);
    EXPECT_EQ(cbssCalculator.calculate(bpm4, oss2), 0);
}
