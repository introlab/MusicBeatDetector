#ifndef UTILS_DATA_PCM_AUDIO_FRAME_H
#define UTILS_DATA_PCM_AUDIO_FRAME_H

#include <Utils/Data/PcmAudioFrameFormat.h>
#include <Utils/Data/AudioFrame.h>
#include <Utils/Data/ArrayToPcmConverter.h>
#include <Utils/Data/PcmToArrayConverter.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <istream>

namespace adaptone
{
    /*
     * A PCM audio frame (Little endian)
     */
    class PcmAudioFrame
    {
        PcmAudioFrameFormat m_format;
        std::size_t m_channelCount;
        std::size_t m_sampleCount;
        uint8_t* m_data;
        bool m_hasOwnership;

    public:
        PcmAudioFrame(PcmAudioFrameFormat format, std::size_t channelCount, std::size_t sampleCount);
        PcmAudioFrame(PcmAudioFrameFormat format, std::size_t channelCount, std::size_t sampleCount, uint8_t* data);

        template<class T>
        PcmAudioFrame(const AudioFrame<T>& other, PcmAudioFrameFormat format);

        PcmAudioFrame(const PcmAudioFrame& other);
        PcmAudioFrame(PcmAudioFrame&& other);
        virtual ~PcmAudioFrame();

        PcmAudioFrameFormat format() const;
        std::size_t channelCount() const;
        std::size_t sampleCount() const;

        uint8_t* data();
        const uint8_t* data() const;
        std::size_t size() const;

        bool hasOwnership() const;

        PcmAudioFrame& operator=(const PcmAudioFrame& other);
        PcmAudioFrame& operator=(PcmAudioFrame&& other);

        uint8_t& operator[](std::size_t i);
        uint8_t operator[](std::size_t i) const;

        void clear();
        void writeChannel(std::size_t thisChannelIndex, const PcmAudioFrame& other, std::size_t otherChannelIndex);

        template<class T>
        operator AudioFrame<T>();

        friend std::istream& operator>>(std::istream& stream, PcmAudioFrame& frame);
        friend std::ostream& operator<<(std::ostream& stream, const PcmAudioFrame& frame);
    };

    template<class T>
    PcmAudioFrame::PcmAudioFrame(const AudioFrame<T>& other, PcmAudioFrameFormat format) :
        PcmAudioFrame(format, other.channelCount(), other.sampleCount())
    {
        ArrayToPcmConverter::convertArrayToPcm(other.data(), m_data, m_sampleCount, m_channelCount, m_format);
    }

    inline PcmAudioFrameFormat PcmAudioFrame::format() const
    {
        return m_format;
    }

    inline std::size_t PcmAudioFrame::channelCount() const
    {
        return m_channelCount;
    }

    inline std::size_t PcmAudioFrame::sampleCount() const
    {
        return m_sampleCount;
    }

    inline uint8_t* PcmAudioFrame::data()
    {
        return m_data;
    }

    inline const uint8_t* PcmAudioFrame::data() const
    {
        return m_data;
    }

    inline std::size_t PcmAudioFrame::size() const
    {
        return adaptone::size(m_format, m_channelCount, m_sampleCount);
    }

    inline bool PcmAudioFrame::hasOwnership() const
    {
        return m_hasOwnership;
    }

    inline uint8_t& PcmAudioFrame::operator[](std::size_t i)
    {
        return m_data[i];
    }

    inline uint8_t PcmAudioFrame::operator[](std::size_t i) const
    {
        return m_data[i];
    }

    inline void PcmAudioFrame::clear()
    {
        std::memset(m_data, 0, size());
    }

    template<class T>
    inline PcmAudioFrame::operator AudioFrame<T>()
    {
        AudioFrame<T> convertedFrame(m_channelCount, m_sampleCount);
        PcmToArrayConverter::convertPcmToArray(m_data, convertedFrame.data(), m_sampleCount, m_channelCount, m_format);
        return convertedFrame;
    }

    inline std::istream& operator>>(std::istream& stream, PcmAudioFrame& frame)
    {
        stream.read(reinterpret_cast<char*>(frame.m_data), frame.size());
        return stream;
    }

    inline std::ostream& operator<<(std::ostream& stream, const PcmAudioFrame& frame)
    {
        stream.write(reinterpret_cast<char*>(frame.m_data), frame.size());
        return stream;
    }
}

#endif
