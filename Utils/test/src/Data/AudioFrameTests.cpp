#include <Utils/Data/AudioFrame.h>

#include <gtest/gtest.h>

using namespace adaptone;
using namespace std;

static constexpr std::size_t ChannelCount = 2;
static constexpr std::size_t SampleCount = 3;
static constexpr std::size_t FrameSize = ChannelCount * SampleCount;

TEST(AudioFrameTests, construtor_shouldSetParameterAndAllocateMemory)
{
    AudioFrame<int> frame(ChannelCount, SampleCount);
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    EXPECT_EQ(frame.channelCount(), ChannelCount);
    EXPECT_EQ(frame.sampleCount(), SampleCount);
    EXPECT_EQ(frame.size(), FrameSize);
    EXPECT_EQ(frame.byteSize(), 24);
    EXPECT_TRUE(frame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(frame.data()[i], i + 1);
    }
}

TEST(AudioFrameTests, construtor_noCopy_shouldSetParameter)
{
    vector<int> dataVector(ChannelCount * SampleCount);
    AudioFrame<int> frame(ChannelCount, SampleCount, dataVector.data());
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    EXPECT_EQ(frame.channelCount(), ChannelCount);
    EXPECT_EQ(frame.sampleCount(), SampleCount);
    EXPECT_EQ(frame.size(), FrameSize);
    EXPECT_EQ(frame.byteSize(), 24);
    EXPECT_EQ(frame.data(), dataVector.data());
    EXPECT_FALSE(frame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(frame.data()[i], i + 1);
    }
}

TEST(AudioFrameTests, copyConstrutor_shouldCopy)
{
    AudioFrame<int> frame(ChannelCount, SampleCount);
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    AudioFrame<int> copy(frame);

    EXPECT_EQ(copy.channelCount(), ChannelCount);
    EXPECT_EQ(copy.sampleCount(), SampleCount);
    EXPECT_EQ(copy.size(), FrameSize);
    EXPECT_NE(frame.data(), copy.data());
    EXPECT_TRUE(frame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(copy.data()[i], i + 1);
    }
}

TEST(AudioFrameTests, moveConstructor_shouldMove)
{
    AudioFrame<int> frame(ChannelCount, SampleCount);
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    int* data = frame.data();
    AudioFrame<int> movedFrame(move(frame));

    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), FrameSize);
    EXPECT_EQ(movedFrame.data(), data);
    EXPECT_TRUE(frame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

TEST(AudioFrameTests, moveConstructor_ownershipFalse_shouldMove)
{
    vector<int> dataVector(ChannelCount * SampleCount);
    AudioFrame<int> frame(ChannelCount, SampleCount, dataVector.data());
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    int* data = frame.data();
    AudioFrame<int> movedFrame(move(frame));

    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), FrameSize);
    EXPECT_EQ(movedFrame.data(), data);
    EXPECT_FALSE(movedFrame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

TEST(AudioFrameTests, assignationOperator_shouldCopy)
{
    AudioFrame<int> frame(ChannelCount, SampleCount);
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    AudioFrame<int> copy(1, 1);
    copy = frame;

    EXPECT_EQ(copy.channelCount(), ChannelCount);
    EXPECT_EQ(copy.sampleCount(), SampleCount);
    EXPECT_EQ(copy.size(), FrameSize);
    EXPECT_EQ(frame.byteSize(), 24);
    EXPECT_NE(frame.data(), copy.data());
    EXPECT_TRUE(frame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(copy.data()[i], i + 1);
    }
}

TEST(AudioFrameTests, moveAssignationOperator_shouldCopy)
{
    AudioFrame<int> frame(ChannelCount, SampleCount);
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    int* data = frame.data();
    AudioFrame<int> movedFrame(1, 1);
    movedFrame = move(frame);

    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), FrameSize);
    EXPECT_EQ(movedFrame.data(), data);
    EXPECT_TRUE(movedFrame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

TEST(AudioFrameTests, moveAssignationOperator_ownershipFalse_shouldCopy)
{
    vector<int> dataVector(ChannelCount * SampleCount);
    AudioFrame<int> frame(ChannelCount, SampleCount, dataVector.data());
    for (size_t i = 0; i < FrameSize; i++)
    {
        frame[i] = i + 1;
    }

    int* data = frame.data();
    AudioFrame<int> movedFrame(1, 1);
    movedFrame = move(frame);

    EXPECT_EQ(movedFrame.channelCount(), ChannelCount);
    EXPECT_EQ(movedFrame.sampleCount(), SampleCount);
    EXPECT_EQ(movedFrame.size(), FrameSize);
    EXPECT_EQ(movedFrame.data(), data);
    EXPECT_FALSE(movedFrame.hasOwnership());

    for (size_t i = 0; i < FrameSize; i++)
    {
        EXPECT_EQ(movedFrame.data()[i], i + 1);
    }

    EXPECT_EQ(frame.data(), nullptr);
    EXPECT_EQ(frame.channelCount(), 0);
    EXPECT_EQ(frame.sampleCount(), 0);
    EXPECT_EQ(frame.size(), 0);
}

