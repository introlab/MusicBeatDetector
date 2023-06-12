#include <MusicBeatDetector/MusicBeatDetector.h>

#include <gtest/gtest.h>

#include <fstream>
#include <numeric>
#include <vector>
#include <string>

using namespace introlab;
using namespace std;

vector<PcmAudioFrame> getPcmAudioFrames(const string& path, PcmAudioFrameFormat format, size_t frameSampleCount)
{
    std::ifstream file(path, std::ifstream::in);
    vector<PcmAudioFrame> frames;

    while (file.good())
    {
        PcmAudioFrame frame(format, 1, frameSampleCount);
        memset(frame.data(), 0, frame.size());
        file.read(reinterpret_cast<char*>(frame.data()), frame.size());
        frames.push_back(frame);
    }

    return frames;
}

static void detect_shouldReturnTheBpmAndTheBeat(const string& path, PcmAudioFrameFormat format)
{
    constexpr float SamplingFrequency = 44100;
    constexpr size_t FrameSampleCount = 256;

    vector<PcmAudioFrame> frames = getPcmAudioFrames(path, format, FrameSampleCount);
    MusicBeatDetector musicBeatDetector(SamplingFrequency, FrameSampleCount);

    vector<float> bpms;
    size_t beatCount = 0;
    for (const PcmAudioFrame& frame : frames)
    {
        Beat beat = musicBeatDetector.detect(frame);
        bpms.push_back(beat.bpm);
        if (beat.isBeat)
        {
            beatCount++;
        }
    }

    float bpmMean = accumulate(bpms.begin(), bpms.end(), 0.0) / bpms.size();

    EXPECT_NEAR(bpmMean, 109, 5);
    EXPECT_NEAR(beatCount, 17, 2);
}

TEST(MusicBeatDetectorTests, detect_float_shouldReturnTheBpmAndTheBeat)
{
    detect_shouldReturnTheBpmAndTheBeat("resources/beat_float.raw", PcmAudioFrameFormat::Float);
}

TEST(MusicBeatDetectorTests, detect_signed16_shouldReturnTheBpmAndTheBeat)
{
    detect_shouldReturnTheBpmAndTheBeat("resources/beat_signed_16.raw", PcmAudioFrameFormat::Signed16);
}
