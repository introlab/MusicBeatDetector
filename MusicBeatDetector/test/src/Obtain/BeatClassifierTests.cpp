#include <MusicBeatDetector/Obtain/OssCalculator.h>
#include <MusicBeatDetector/Obtain/BpmEstimator.h>
#include <MusicBeatDetector/Obtain/CbssCalculator.h>
#include <MusicBeatDetector/Obtain/BeatClassifier.h>

#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>

#include <gtest/gtest.h>

using namespace introlab;
using namespace std;

TEST(BeatClassifierTests, constructor_invalidMinBpm_shouldThrowNotSupportedException)
{
    constexpr float OssSamplingFrequency = 44100.0 / 128;
    constexpr float MinBpm = 0;

    EXPECT_THROW(BeatClassifier(OssSamplingFrequency, MinBpm), NotSupportedException);
}

TEST(BeatClassifierTests, calculate_shouldReturneTheBeatClass)
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
    BeatClassifier beatClassifier(OssSamplingFrequency, MinBpm);

    float oss1 = ossCalculator.calculate(frame1);
    float oss2 = ossCalculator.calculate(frame2);

    float bpm1 = bpmEstimator.estimate(oss1);
    float bpm2 = bpmEstimator.estimate(oss2);
    float bpm3 = bpmEstimator.estimate(oss1);
    float bpm4 = bpmEstimator.estimate(oss2);

    float cbss1 = cbssCalculator.calculate(bpm1, oss1);
    float cbss2 = cbssCalculator.calculate(bpm2, oss2);
    float cbss3 = cbssCalculator.calculate(bpm3, oss1);
    float cbss4 = cbssCalculator.calculate(bpm4, oss2);

    EXPECT_EQ(beatClassifier.classify(bpm1, cbss1), false);
    EXPECT_EQ(beatClassifier.classify(bpm2, cbss2), true);
    EXPECT_EQ(beatClassifier.classify(bpm3, cbss3), false);
    EXPECT_EQ(beatClassifier.classify(bpm4, cbss4), true);
}
