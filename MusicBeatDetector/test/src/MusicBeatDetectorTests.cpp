#include <MusicBeatDetector/MusicBeatDetector.h>

#include <gtest/gtest.h>

using namespace introlab;

TEST(MusicBeatDetectorTests, detect_shouldReturnTheBpmAndTheBeatClass)
{
    constexpr float SamplingFrequency = 44100;
    constexpr size_t FrameSampleCount = 128;
    MusicBeatDetector musicBeatDetector(SamplingFrequency, FrameSampleCount);
}
