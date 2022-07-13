#include <MusicBeatDetector/Utils/Data/PcmAudioFrame.h>

#include <MusicBeatDetector/Utils/Exception/InvalidValueException.h>

#include <gtest/gtest.h>

#include <sstream>
#include <chrono>

using namespace introlab;
using namespace std;

static constexpr std::size_t ChannelCount = 2;
static constexpr std::size_t SampleCount = 3;

TEST(PcmAudioFrameTests, constructor_shouldSetParameterAndAllocateMemory)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Signed24, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    EXPECT_EQ(frame.format(), PcmAudioFrameFormat::Signed24);
    EXPECT_EQ(frame.channelCount(), ChannelCount);
    EXPECT_EQ(frame.sampleCount(), SampleCount);
    EXPECT_EQ(frame.size(), 18);
    EXPECT_TRUE(frame.hasOwnership());

    for (size_t i = 0; i < frame.size(); i++)
    {
        EXPECT_EQ(frame.data()[i], i + 1);
    }
}

TEST(PcmAudioFrameTests, constructor_noCopy_shouldSetParameter)
{
    vector<uint8_t> dataVector(formatSize(PcmAudioFrameFormat::Signed24) * ChannelCount * SampleCount);
    PcmAudioFrame frame(PcmAudioFrameFormat::Signed24, ChannelCount, SampleCount, dataVector.data());
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    EXPECT_EQ(frame.format(), PcmAudioFrameFormat::Signed24);
    EXPECT_EQ(frame.channelCount(), ChannelCount);
    EXPECT_EQ(frame.sampleCount(), SampleCount);
    EXPECT_EQ(frame.size(), 18);
    EXPECT_FALSE(frame.hasOwnership());

    for (size_t i = 0; i < frame.size(); i++)
    {
        EXPECT_EQ(frame.data()[i], i + 1);
    }
}

TEST(PcmAudioFrameTests, constructor_packedAudioFrame_shouldConvertTheFrame)
{
    PackedAudioFrame<float> frame(ChannelCount, SampleCount);

    frame[0] = -1;
    frame[1] = 1;
    frame[2] = -0.5;

    frame[3] = 0;
    frame[4] = 0.5;
    frame[5] = 0.25;

    PcmAudioFrame convertedFrame(frame, PcmAudioFrameFormat::Unsigned8);

    ASSERT_EQ(convertedFrame.size(), 6);
    EXPECT_TRUE(convertedFrame.hasOwnership());

    EXPECT_EQ(convertedFrame[0], 0);
    EXPECT_EQ(convertedFrame[1], 128);
    EXPECT_EQ(convertedFrame[2], 255);
    EXPECT_EQ(convertedFrame[3], 191);
    EXPECT_EQ(convertedFrame[4], 64);
    EXPECT_EQ(convertedFrame[5], 159);
}

TEST(PcmAudioFrameTests, copyConstructor_shouldCopy)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Signed24, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    PcmAudioFrame copy(frame);

    EXPECT_EQ(copy.format(), PcmAudioFrameFormat::Signed24);
    EXPECT_EQ(copy.channelCount(), ChannelCount);
    EXPECT_EQ(copy.sampleCount(), SampleCount);
    EXPECT_EQ(copy.size(), 18);
    EXPECT_TRUE(copy.hasOwnership());
    EXPECT_NE(frame.data(), copy.data());

    for (size_t i = 0; i < copy.size(); i++)
    {
        EXPECT_EQ(copy.data()[i], i + 1);
    }
}

TEST(PcmAudioFrameTests, moveConstructor_shouldMove)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Signed24, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    const uint8_t* data = frame.data();
    const PcmAudioFrame movedFrame(move(frame));

    EXPECT_EQ(movedFrame.format(), PcmAudioFrameFormat::Signed24);
    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), 18);
    EXPECT_TRUE(movedFrame.hasOwnership());
    EXPECT_EQ(movedFrame.data(), data);

    for (size_t i = 0; i < movedFrame.size(); i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
        EXPECT_EQ(movedFrame[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

TEST(PcmAudioFrameTests, moveConstructor_ownershipFalse_shouldMove)
{
    vector<uint8_t> dataVector(formatSize(PcmAudioFrameFormat::Signed24) * ChannelCount * SampleCount);
    PcmAudioFrame frame(PcmAudioFrameFormat::Signed24, ChannelCount, SampleCount, dataVector.data());
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    const uint8_t* data = frame.data();
    const PcmAudioFrame movedFrame(move(frame));

    EXPECT_EQ(movedFrame.format(), PcmAudioFrameFormat::Signed24);
    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), 18);
    EXPECT_FALSE(movedFrame.hasOwnership());
    EXPECT_EQ(movedFrame.data(), data);

    for (size_t i = 0; i < movedFrame.size(); i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
        EXPECT_EQ(movedFrame[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

TEST(PcmAudioFrameTests, assignationOperator_shouldCopy)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Signed24, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    PcmAudioFrame copy(PcmAudioFrameFormat::Signed16, 200, 300);
    uint8_t* oldDataBuffer = copy.data();
    copy = frame;

    EXPECT_NE(oldDataBuffer, copy.data());
    EXPECT_EQ(copy.format(), PcmAudioFrameFormat::Signed24);
    EXPECT_EQ(copy.channelCount(), ChannelCount);
    EXPECT_EQ(copy.sampleCount(), SampleCount);
    EXPECT_EQ(copy.size(), 18);
    EXPECT_TRUE(copy.hasOwnership());
    EXPECT_NE(frame.data(), copy.data());

    for (size_t i = 0; i < copy.size(); i++)
    {
        EXPECT_EQ(copy.data()[i], i + 1);
    }
}

TEST(PcmAudioFrameTests, assignationOperator_same_shouldCopyWithoutMemoryAllocation)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Signed16, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    PcmAudioFrame copy(PcmAudioFrameFormat::Signed16, ChannelCount, SampleCount);
    uint8_t* oldDataBuffer = copy.data();
    copy = frame;

    EXPECT_EQ(oldDataBuffer, copy.data());
    EXPECT_EQ(copy.format(), PcmAudioFrameFormat::Signed16);
    EXPECT_EQ(copy.channelCount(), ChannelCount);
    EXPECT_EQ(copy.sampleCount(), SampleCount);
    EXPECT_EQ(copy.size(), 12);
    EXPECT_TRUE(copy.hasOwnership());
    EXPECT_NE(frame.data(), copy.data());

    for (size_t i = 0; i < copy.size(); i++)
    {
        EXPECT_EQ(copy.data()[i], i + 1);
    }
}

TEST(PcmAudioFrameTests, moveAssignationOperator_shouldMove)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Unsigned24, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    const uint8_t* data = frame.data();
    PcmAudioFrame movedFrame(PcmAudioFrameFormat::Signed16, 1, 1);
    movedFrame = move(frame);

    EXPECT_EQ(movedFrame.format(), PcmAudioFrameFormat::Unsigned24);
    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), 18);
    EXPECT_TRUE(movedFrame.hasOwnership());
    EXPECT_EQ(movedFrame.data(), data);

    for (size_t i = 0; i < movedFrame.size(); i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

TEST(PcmAudioFrameTests, moveAssignationOperator_ownershipFalse_shouldMove)
{
    vector<uint8_t> dataVector(formatSize(PcmAudioFrameFormat::Unsigned24) * ChannelCount * SampleCount);
    PcmAudioFrame frame(PcmAudioFrameFormat::Unsigned24, ChannelCount, SampleCount, dataVector.data());
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    const uint8_t* data = frame.data();
    PcmAudioFrame movedFrame(PcmAudioFrameFormat::Signed16, 1, 1);
    movedFrame = move(frame);

    EXPECT_EQ(movedFrame.format(), PcmAudioFrameFormat::Unsigned24);
    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), 18);
    EXPECT_FALSE(movedFrame.hasOwnership());
    EXPECT_EQ(movedFrame.data(), data);

    for (size_t i = 0; i < movedFrame.size(); i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

TEST(PcmAudioFrameTests, assignationOperator_packedAudioFrame_shouldCopy)
{
    PackedAudioFrame<float> frame(ChannelCount, SampleCount);

    frame[0] = -1;
    frame[1] = 1;
    frame[2] = -0.5;

    frame[3] = 0;
    frame[4] = 0.5;
    frame[5] = 0.25;

    PcmAudioFrame pcmFrame(PcmAudioFrameFormat::Unsigned8, 200, 300);
    uint8_t* oldPcmDataBuffer = pcmFrame.data();
    pcmFrame = frame;

    EXPECT_NE(oldPcmDataBuffer, pcmFrame.data());
    EXPECT_EQ(pcmFrame.format(), PcmAudioFrameFormat::Unsigned8);
    EXPECT_EQ(pcmFrame.channelCount(), ChannelCount);
    EXPECT_EQ(pcmFrame.sampleCount(), SampleCount);
    EXPECT_EQ(pcmFrame.size(), 6);
    EXPECT_TRUE(pcmFrame.hasOwnership());

    EXPECT_EQ(pcmFrame[0], 0);
    EXPECT_EQ(pcmFrame[1], 128);
    EXPECT_EQ(pcmFrame[2], 255);
    EXPECT_EQ(pcmFrame[3], 191);
    EXPECT_EQ(pcmFrame[4], 64);
    EXPECT_EQ(pcmFrame[5], 159);
}

TEST(PcmAudioFrameTests, assignationOperator_samePackedAudioFrame_shouldCopyWithoutMemoryAllocation)
{
    PackedAudioFrame<float> frame(ChannelCount, SampleCount);

    frame[0] = -1;
    frame[1] = 1;
    frame[2] = -0.5;

    frame[3] = 0;
    frame[4] = 0.5;
    frame[5] = 0.25;

    PcmAudioFrame pcmFrame(PcmAudioFrameFormat::Unsigned8, ChannelCount, SampleCount);
    uint8_t* oldPcmDataBuffer = pcmFrame.data();
    pcmFrame = frame;

    EXPECT_EQ(oldPcmDataBuffer, pcmFrame.data());
    EXPECT_EQ(pcmFrame.format(), PcmAudioFrameFormat::Unsigned8);
    EXPECT_EQ(pcmFrame.channelCount(), ChannelCount);
    EXPECT_EQ(pcmFrame.sampleCount(), SampleCount);
    EXPECT_EQ(pcmFrame.size(), 6);
    EXPECT_TRUE(pcmFrame.hasOwnership());

    EXPECT_EQ(pcmFrame[0], 0);
    EXPECT_EQ(pcmFrame[1], 128);
    EXPECT_EQ(pcmFrame[2], 255);
    EXPECT_EQ(pcmFrame[3], 191);
    EXPECT_EQ(pcmFrame[4], 64);
    EXPECT_EQ(pcmFrame[5], 159);
}

TEST(PcmAudioFrameTests, clear_shouldSetAllBytesTo0)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Unsigned8, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }
    frame.clear();

    for (size_t i = 0; i < frame.size(); i++)
    {
        EXPECT_EQ(frame.data()[i], 0);
    }
}

TEST(PcmAudioFrameTests, slice_shouldReturnBorrowedSlice)
{
    PcmAudioFrame frame(PcmAudioFrameFormat::Unsigned16, ChannelCount, SampleCount);
    for (size_t i = 0; i < frame.size(); i++)
    {
        frame[i] = i + 1;
    }

    PcmAudioFrame slice1 = frame.slice(0, 1);
    PcmAudioFrame slice2 = frame.slice(1, 2);
    PcmAudioFrame slice3 = frame.slice(2, 1);

    constexpr uint8_t ExpectedSlice1[] = {1, 2, 3, 4};
    constexpr uint8_t ExpectedSlice2[] = {5, 6, 7, 8, 9, 10, 11, 12};
    constexpr uint8_t ExpectedSlice3[] = {9, 10, 11, 12};

    EXPECT_FALSE(slice1.hasOwnership());
    ASSERT_EQ(slice1.size(), 4);
    EXPECT_EQ(memcmp(slice1.data(), ExpectedSlice1, slice1.size()), 0);

    EXPECT_FALSE(slice2.hasOwnership());
    ASSERT_EQ(slice2.size(), 8);
    EXPECT_EQ(memcmp(slice2.data(), ExpectedSlice2, slice2.size()), 0);

    EXPECT_FALSE(slice3.hasOwnership());
    ASSERT_EQ(slice3.size(), 4);
    EXPECT_EQ(memcmp(slice3.data(), ExpectedSlice3, slice3.size()), 0);
}

TEST(PcmAudioFrameTests, writeChannel_shouldWriteTheSpecifiedChannel)
{
    PcmAudioFrame frame0(PcmAudioFrameFormat::Unsigned24, ChannelCount, ChannelCount);
    PcmAudioFrame frame1(PcmAudioFrameFormat::Unsigned24, SampleCount, ChannelCount);
    for (size_t i = 0; i < frame0.size(); i++)
    {
        frame0[i] = i + 1;
    }

    frame1.clear();
    frame1.writeChannel(1, frame0, 0);
    frame1.writeChannel(0, frame0, 1);

    EXPECT_EQ(frame1[0], 4);
    EXPECT_EQ(frame1[1], 5);
    EXPECT_EQ(frame1[2], 6);

    EXPECT_EQ(frame1[3], 1);
    EXPECT_EQ(frame1[4], 2);
    EXPECT_EQ(frame1[5], 3);

    EXPECT_EQ(frame1[6], 0);
    EXPECT_EQ(frame1[7], 0);
    EXPECT_EQ(frame1[8], 0);

    EXPECT_EQ(frame1[9], 10);
    EXPECT_EQ(frame1[10], 11);
    EXPECT_EQ(frame1[11], 12);

    EXPECT_EQ(frame1[12], 7);
    EXPECT_EQ(frame1[13], 8);
    EXPECT_EQ(frame1[14], 9);

    EXPECT_EQ(frame1[15], 0);
    EXPECT_EQ(frame1[16], 0);
    EXPECT_EQ(frame1[17], 0);
}

TEST(PcmAudioFrameTests, writeChannel_performance)
{
    PcmAudioFrame frame0(PcmAudioFrameFormat::Unsigned32, 1, 256);
    PcmAudioFrame frame1(PcmAudioFrameFormat::Unsigned32, 16, 256);
    for (size_t i = 0; i < frame0.size(); i++)
    {
        frame0[i] = i + 1;
    }

    constexpr size_t Count = 10000;

    double minElapsedTimeSeconds = 1;
    double maxElapsedTimeSeconds = 0;
    double totalElapsedTimeSeconds = 0;

    for (size_t i = 0; i < Count; i++)
    {
        auto start = chrono::system_clock::now();

        frame1.clear();
        frame1.writeChannel(0, frame0, i % frame1.channelCount());

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsedSeconds = end - start;

        totalElapsedTimeSeconds += elapsedSeconds.count();
        minElapsedTimeSeconds =
            elapsedSeconds.count() < minElapsedTimeSeconds ? elapsedSeconds.count() : minElapsedTimeSeconds;
        maxElapsedTimeSeconds =
            elapsedSeconds.count() > maxElapsedTimeSeconds ? elapsedSeconds.count() : maxElapsedTimeSeconds;
    }

    cout << "Elapsed time (avg) = " << totalElapsedTimeSeconds / Count << " s" << endl;
    cout << "Elapsed time (min) = " << minElapsedTimeSeconds << " s" << endl;
    cout << "Elapsed time (max) = " << maxElapsedTimeSeconds << " s" << endl;
}

TEST(PcmAudioFrameTests, audioFrameConversionOperator_shouldConvertTheFrame)
{
    constexpr float MaxAbsError = 0.1;
    PcmAudioFrame frame(PcmAudioFrameFormat::Unsigned8, ChannelCount, SampleCount);

    frame[0] = 0;
    frame[1] = 128;
    frame[2] = 255;
    frame[3] = 191;
    frame[4] = 64;
    frame[5] = 159;

    PackedAudioFrame<float> convertedFrame(frame);

    ASSERT_EQ(convertedFrame.size(), 6);
    EXPECT_TRUE(convertedFrame.hasOwnership());

    EXPECT_NEAR(convertedFrame[0], -1, MaxAbsError);
    EXPECT_NEAR(convertedFrame[1], 1, MaxAbsError);
    EXPECT_NEAR(convertedFrame[2], -0.5, MaxAbsError);

    EXPECT_NEAR(convertedFrame[3], 0, MaxAbsError);
    EXPECT_NEAR(convertedFrame[4], 0.5, MaxAbsError);
    EXPECT_NEAR(convertedFrame[5], 0.25, MaxAbsError);
}

TEST(PcmAudioFrameTests, copyTo_packedAudioFrame_shouldCopy)
{
    constexpr float MaxAbsError = 0.1;
    PcmAudioFrame pcmFrame(PcmAudioFrameFormat::Unsigned8, ChannelCount, SampleCount);

    pcmFrame[0] = 0;
    pcmFrame[1] = 128;
    pcmFrame[2] = 255;
    pcmFrame[3] = 191;
    pcmFrame[4] = 64;
    pcmFrame[5] = 159;

    PackedAudioFrame<float> frame(200, 300);
    float* oldDataBuffer = frame.data();
    pcmFrame.copyTo(frame);

    EXPECT_NE(oldDataBuffer, frame.data());
    ASSERT_EQ(frame.size(), 6);
    EXPECT_TRUE(frame.hasOwnership());

    EXPECT_NEAR(frame[0], -1, MaxAbsError);
    EXPECT_NEAR(frame[1], 1, MaxAbsError);
    EXPECT_NEAR(frame[2], -0.5, MaxAbsError);

    EXPECT_NEAR(frame[3], 0, MaxAbsError);
    EXPECT_NEAR(frame[4], 0.5, MaxAbsError);
    EXPECT_NEAR(frame[5], 0.25, MaxAbsError);
}

TEST(PcmAudioFrameTests, copyTo_samePackedAudioFrame_shouldCopyWithoutMemoryAllocation)
{
    constexpr float MaxAbsError = 0.1;
    PcmAudioFrame pcmFrame(PcmAudioFrameFormat::Unsigned8, ChannelCount, SampleCount);

    pcmFrame[0] = 0;
    pcmFrame[1] = 128;
    pcmFrame[2] = 255;
    pcmFrame[3] = 191;
    pcmFrame[4] = 64;
    pcmFrame[5] = 159;

    PackedAudioFrame<float> frame(ChannelCount, SampleCount);
    float* oldDataBuffer = frame.data();
    pcmFrame.copyTo(frame);

    EXPECT_EQ(oldDataBuffer, frame.data());
    ASSERT_EQ(frame.size(), 6);
    EXPECT_TRUE(frame.hasOwnership());

    EXPECT_NEAR(frame[0], -1, MaxAbsError);
    EXPECT_NEAR(frame[1], 1, MaxAbsError);
    EXPECT_NEAR(frame[2], -0.5, MaxAbsError);

    EXPECT_NEAR(frame[3], 0, MaxAbsError);
    EXPECT_NEAR(frame[4], 0.5, MaxAbsError);
    EXPECT_NEAR(frame[5], 0.25, MaxAbsError);
}

TEST(PcmAudioFrameTests, extractionOperator_shouldExtractDataFromTheStream)
{
    stringstream ss;
    ss << "ab";

    PcmAudioFrame frame(PcmAudioFrameFormat::Unsigned8, ChannelCount, 1);

    ss >> frame;

    EXPECT_EQ(frame.data()[0], 'a');
    EXPECT_EQ(frame.data()[1], 'b');
}

TEST(PcmAudioFrameTests, insertionOperator_shouldInsertDataIntoTheStream)
{
    stringstream ss;
    PcmAudioFrame frame(PcmAudioFrameFormat::Unsigned8, ChannelCount, 1);
    frame[0] = 'a';
    frame[1] = 'b';

    ss << frame;

    EXPECT_EQ(ss.str(), "ab");
}
