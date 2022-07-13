#ifndef MUSIC_BEAT_DETECTOR_UTILS_DATA_PCM_AUDIO_FRAME_H
#define MUSIC_BEAT_DETECTOR_UTILS_DATA_PCM_AUDIO_FRAME_H

#include <MusicBeatDetector/Utils/Data/PcmAudioFrameFormat.h>
#include <MusicBeatDetector/Utils/Data/PackedAudioFrame.h>
#include <MusicBeatDetector/Utils/Data/ArrayToPcmConverter.h>
#include <MusicBeatDetector/Utils/Data/PcmToArrayConverter.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <istream>

namespace introlab
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
        PcmAudioFrame(const PackedAudioFrame<T>& other, PcmAudioFrameFormat format);

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

        template<class T>
        PcmAudioFrame& operator=(const PackedAudioFrame<T>& other);

        uint8_t& operator[](std::size_t i);
        uint8_t operator[](std::size_t i) const;

        void clear();
        PcmAudioFrame slice(size_t sampleIndex, size_t sampleCount);
        void writeChannel(std::size_t thisChannelIndex, const PcmAudioFrame& other, std::size_t otherChannelIndex);

        template<class T>
        operator PackedAudioFrame<T>() const;
        template<class T>
        void copyTo(PackedAudioFrame<T>& other) const;

        friend std::istream& operator>>(std::istream& stream, PcmAudioFrame& frame);
        friend std::ostream& operator<<(std::ostream& stream, const PcmAudioFrame& frame);
    };

    template<class T>
    PcmAudioFrame::PcmAudioFrame(const PackedAudioFrame<T>& other, PcmAudioFrameFormat format)
        : PcmAudioFrame(format, other.channelCount(), other.sampleCount())
    {
        ArrayToPcmConverter::convertArrayToPcm(other.data(), m_data, m_sampleCount, m_channelCount, m_format);
    }

    inline PcmAudioFrameFormat PcmAudioFrame::format() const { return m_format; }

    inline std::size_t PcmAudioFrame::channelCount() const { return m_channelCount; }

    inline std::size_t PcmAudioFrame::sampleCount() const { return m_sampleCount; }

    inline uint8_t* PcmAudioFrame::data() { return m_data; }

    inline const uint8_t* PcmAudioFrame::data() const { return m_data; }

    inline std::size_t PcmAudioFrame::size() const { return introlab::size(m_format, m_channelCount, m_sampleCount); }

    inline bool PcmAudioFrame::hasOwnership() const { return m_hasOwnership; }

    template<class T>
    inline PcmAudioFrame& PcmAudioFrame::operator=(const PackedAudioFrame<T>& other)
    {
        if (m_channelCount != other.channelCount() || m_sampleCount != other.sampleCount())
        {
            if (m_data != nullptr && m_hasOwnership)
            {
                delete[] m_data;
            }

            m_channelCount = other.channelCount();
            m_sampleCount = other.sampleCount();
            m_hasOwnership = true;

            m_data = new uint8_t[size()];
        }
        ArrayToPcmConverter::convertArrayToPcm(other.data(), m_data, m_sampleCount, m_channelCount, m_format);

        return *this;
    }

    inline uint8_t& PcmAudioFrame::operator[](std::size_t i) { return m_data[i]; }

    inline uint8_t PcmAudioFrame::operator[](std::size_t i) const { return m_data[i]; }

    inline void PcmAudioFrame::clear() { std::memset(m_data, 0, size()); }

    inline PcmAudioFrame PcmAudioFrame::slice(size_t sampleIndex, size_t sampleCount)
    {
        uint8_t* data = m_data + introlab::size(m_format, m_channelCount, sampleIndex);
        return PcmAudioFrame(m_format, m_channelCount, sampleCount, data);
    }

    template<class T>
    inline PcmAudioFrame::operator PackedAudioFrame<T>() const
    {
        PackedAudioFrame<T> convertedFrame(m_channelCount, m_sampleCount);
        PcmToArrayConverter::convertPcmToArray(m_data, convertedFrame.data(), m_sampleCount, m_channelCount, m_format);
        return convertedFrame;
    }

    template<class T>
    void PcmAudioFrame::copyTo(PackedAudioFrame<T>& other) const
    {
        if (m_channelCount != other.channelCount() || m_sampleCount != other.sampleCount())
        {
            other = *this;
        }
        else
        {
            PcmToArrayConverter::convertPcmToArray(m_data, other.data(), m_sampleCount, m_channelCount, m_format);
        }
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
