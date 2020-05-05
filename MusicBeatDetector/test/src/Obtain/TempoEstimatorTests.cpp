#include <MusicBeatDetector/Obtain/OssCalculator.h>
#include <MusicBeatDetector/Obtain/TempoEstimator.h>

#include <Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(TempoEstimatorTests, constructor_negativeMinBpm_range)
{
    constexpr float OssSamplingFrequency = 344.5;
    constexpr size_t OssWindowSize = 1024;
    constexpr float MinBpm = -49.93;
    constexpr float MaxBpm = 210.94;

    EXPECT_THROW(TempoEstimator(OssSamplingFrequency, OssWindowSize, MinBpm, MaxBpm), NotSupportedException);
}

TEST(TempoEstimatorTests, constructor_negativeMaxBpm_range)
{
    constexpr float OssSamplingFrequency = 344.5;
    constexpr size_t OssWindowSize = 1024;
    constexpr float MinBpm = 49.93;
    constexpr float MaxBpm = -210.94;

    EXPECT_THROW(TempoEstimator(OssSamplingFrequency, OssWindowSize, MinBpm, MaxBpm), NotSupportedException);
}

TEST(TempoEstimatorTests, constructor_invalidLagRange_range)
{
    constexpr float OssSamplingFrequency = 344.5;
    constexpr size_t OssWindowSize = 256;
    constexpr float MinBpm = 10;
    constexpr float MaxBpm = 9;

    EXPECT_THROW(TempoEstimator(OssSamplingFrequency, OssWindowSize, MinBpm, MaxBpm), NotSupportedException);
}

TEST(TempoEstimatorTests, constructor_invalidOssWindowSize_range)
{
    constexpr float OssSamplingFrequency = 344.5;
    constexpr size_t OssWindowSize = 10;
    constexpr float MinBpm = 10;
    constexpr float MaxBpm = 9;

    EXPECT_THROW(TempoEstimator(OssSamplingFrequency, OssWindowSize, MinBpm, MaxBpm), NotSupportedException);
}

TEST(TempoEstimatorTests, estimateTempo_shouldReturnTempo)
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
    TempoEstimator tempoEstimator(OssSamplingFrequency, OssWindowSize, MinBpm, MaxBpm);

    float oss1 = ossCalculator.calculate(frame1);
    float oss2 = ossCalculator.calculate(frame2);

    EXPECT_EQ(tempoEstimator.estimateTempo(oss1), 20670);
    EXPECT_EQ(tempoEstimator.estimateTempo(oss2), 20670);
    EXPECT_EQ(tempoEstimator.estimateTempo(oss1), 20670);
    EXPECT_EQ(tempoEstimator.estimateTempo(oss2), 20670);
}
