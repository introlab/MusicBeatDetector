#include <Utils/Data/PcmAudioFrame.h>

#include <Utils/Exception/InvalidValueException.h>

using namespace adaptone;
using namespace std;

PcmAudioFrame::PcmAudioFrame(PcmAudioFrameFormat format, size_t channelCount, size_t sampleCount) :
    m_format(format), m_channelCount(channelCount), m_sampleCount(sampleCount), m_hasOwnership(true)
{
    m_data = new uint8_t[size()];
}

PcmAudioFrame::PcmAudioFrame(PcmAudioFrameFormat format, size_t channelCount, size_t sampleCount, uint8_t* data) :
    m_format(format), m_channelCount(channelCount), m_sampleCount(sampleCount), m_data(data), m_hasOwnership(false)
{
}

PcmAudioFrame::PcmAudioFrame(const PcmAudioFrame& other) :
    m_format(other.m_format),
    m_channelCount(other.m_channelCount),
    m_sampleCount(other.m_sampleCount),
    m_hasOwnership(true)
{
    m_data = new uint8_t[size()];
    memcpy(m_data, other.m_data, size());
}

PcmAudioFrame::PcmAudioFrame(PcmAudioFrame&& other) :
    m_format(other.m_format),
    m_channelCount(other.m_channelCount),
    m_sampleCount(other.m_sampleCount),
    m_hasOwnership(other.m_hasOwnership)
{
    m_data = other.m_data;

    other.m_channelCount = 0;
    other.m_sampleCount = 0;
    other.m_data = nullptr;
}

PcmAudioFrame::~PcmAudioFrame()
{
    if (m_data != nullptr && m_hasOwnership)
    {
        delete[] m_data;
    }
}

PcmAudioFrame& PcmAudioFrame::operator=(const PcmAudioFrame& other)
{
    if (m_format != other.m_format || m_channelCount != other.m_channelCount || m_sampleCount != other.m_sampleCount)
    {
        if (m_data != nullptr && m_hasOwnership)
        {
            delete[] m_data;
        }

        m_format = other.m_format;
        m_channelCount = other.m_channelCount;
        m_sampleCount = other.m_sampleCount;
        m_hasOwnership = true;

        m_data = new uint8_t[size()];
    }
    memcpy(m_data, other.m_data, size());

    return *this;
}

PcmAudioFrame& PcmAudioFrame::operator=(PcmAudioFrame&& other)
{
    if (m_data != nullptr && m_hasOwnership)
    {
        delete[] m_data;
    }

    m_format = other.m_format;
    m_channelCount = other.m_channelCount;
    m_sampleCount = other.m_sampleCount;
    m_data = other.m_data;
    m_hasOwnership = other.m_hasOwnership;

    other.m_channelCount = 0;
    other.m_sampleCount = 0;
    other.m_data = nullptr;

    return *this;
}

void PcmAudioFrame::writeChannel(size_t thisChannelIndex, const PcmAudioFrame& other, size_t otherChannelIndex)
{
    if (other.m_format != m_format || other.m_sampleCount != m_sampleCount)
    {
        THROW_INVALID_VALUE_EXCEPTION("format, sampleCount", "");
    }

    size_t sampleSize = formatSize(m_format);
    for (size_t i = 0; i < other.m_sampleCount; i++)
    {
        size_t thisDataIndex = (i * m_channelCount + thisChannelIndex) * sampleSize;
        size_t otherDataIndex = (i * other.m_channelCount + otherChannelIndex) * sampleSize;

        for (size_t j = 0; j < sampleSize; j++)
        {
            m_data[thisDataIndex + j] = other.m_data[otherDataIndex + j];
        }
    }
}
