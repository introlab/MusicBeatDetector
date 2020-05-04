#ifndef UTILS_DATA_AUDIO_FRAME_H
#define UTILS_DATA_AUDIO_FRAME_H

#include <cstddef>
#include <cstring>

namespace adaptone
{
    /*
     * A templated audio frame. The channel samples are consecutive.
     */
    template<class T>
    class AudioFrame
    {
        std::size_t m_channelCount;
        std::size_t m_sampleCount;
        T* m_data;
        bool m_hasOwnership;

    public:
        AudioFrame(std::size_t channelCount, std::size_t sampleCount);
        AudioFrame(std::size_t channelCount, std::size_t sampleCount, T* data);
        AudioFrame(const AudioFrame& other);
        AudioFrame(AudioFrame&& other);
        virtual ~AudioFrame();

        std::size_t channelCount() const;
        std::size_t sampleCount() const;

        T* data();
        const T* data() const;
        std::size_t size() const;
        std::size_t byteSize() const;

        bool hasOwnership() const;

        T& operator[](std::size_t i);
        const T& operator[](std::size_t i) const;

        AudioFrame& operator=(const AudioFrame& other);
        AudioFrame& operator=(AudioFrame&& other);
    };

    template<class T>
    inline AudioFrame<T>::AudioFrame(std::size_t channelCount, std::size_t sampleCount) :
        m_channelCount(channelCount), m_sampleCount(sampleCount), m_hasOwnership(true)
    {
        m_data = new T[m_channelCount * m_sampleCount];
    }

    template<class T>
    inline AudioFrame<T>::AudioFrame(std::size_t channelCount, std::size_t sampleCount, T* data) :
        m_channelCount(channelCount), m_sampleCount(sampleCount), m_data(data), m_hasOwnership(false)
    {
    }

    template<class T>
    inline AudioFrame<T>::AudioFrame(const AudioFrame<T>& other) :
        m_channelCount(other.m_channelCount), m_sampleCount(other.m_sampleCount), m_hasOwnership(true)
    {
        m_data = new T[m_channelCount * m_sampleCount];
        std::memcpy(m_data, other.m_data, m_channelCount * m_sampleCount * sizeof(T));
    }

    template<class T>
    inline AudioFrame<T>::AudioFrame(AudioFrame<T>&& other):
        m_channelCount(other.m_channelCount), m_sampleCount(other.m_sampleCount), m_hasOwnership(other.m_hasOwnership)
    {
        m_data = other.m_data;

        other.m_channelCount = 0;
        other.m_sampleCount = 0;
        other.m_data = nullptr;
    }

    template<class T>
    inline AudioFrame<T>::~AudioFrame()
    {
        if (m_data != nullptr && m_hasOwnership)
        {
            delete[] m_data;
        }
    }

    template<class T>
    inline std::size_t AudioFrame<T>::channelCount() const
    {
        return m_channelCount;
    }

    template<class T>
    inline std::size_t AudioFrame<T>::sampleCount() const
    {
        return m_sampleCount;
    }

    template<class T>
    inline T* AudioFrame<T>::data()
    {
        return m_data;
    }

    template<class T>
    inline const T* AudioFrame<T>::data() const
    {
        return m_data;
    }

    template<class T>
    inline std::size_t AudioFrame<T>::size() const
    {
        return m_channelCount * m_sampleCount;
    }

    template<class T>
    inline std::size_t AudioFrame<T>::byteSize() const
    {
        return m_channelCount * m_sampleCount * sizeof(T);
    }

    template<class T>
    inline bool AudioFrame<T>::hasOwnership() const
    {
        return m_hasOwnership;
    }

    template<class T>
    inline T& AudioFrame<T>::operator[](std::size_t i)
    {
        return m_data[i];
    }

    template<class T>
    inline const T& AudioFrame<T>::operator[](std::size_t i) const
    {
        return m_data[i];
    }

    template<class T>
    inline AudioFrame<T>& AudioFrame<T>::operator=(const AudioFrame<T>& other)
    {
        if (m_data != nullptr && m_hasOwnership)
        {
            delete[] m_data;
        }

        m_channelCount = other.m_channelCount;
        m_sampleCount = other.m_sampleCount;
        m_hasOwnership = true;

        m_data = new T[m_channelCount * m_sampleCount];
        std::memcpy(m_data, other.m_data, m_channelCount * m_sampleCount * sizeof(T));

        return *this;
    }

    template<class T>
    inline AudioFrame<T>& AudioFrame<T>::operator=(AudioFrame<T>&& other)
    {
        if (m_data != nullptr && m_hasOwnership)
        {
            delete[] m_data;
        }

        m_channelCount = other.m_channelCount;
        m_sampleCount = other.m_sampleCount;
        m_data = other.m_data;
        m_hasOwnership = other.m_hasOwnership;

        other.m_channelCount = 0;
        other.m_sampleCount = 0;
        other.m_data = nullptr;

        return *this;
    }
}

#endif

