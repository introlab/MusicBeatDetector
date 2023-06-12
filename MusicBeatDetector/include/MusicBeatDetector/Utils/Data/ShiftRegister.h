#ifndef MUSIC_BEAT_DETECTOR_UTILS_DATA_SHIFT_REGISTER_H
#define MUSIC_BEAT_DETECTOR_UTILS_DATA_SHIFT_REGISTER_H

#include <vector>
#include <initializer_list>
#include <cstdint>

namespace introlab
{
    template<class T>
    class ShiftRegister
    {
        int64_t m_currentIndex;
        std::vector<T> m_data;

    public:
        ShiftRegister(std::size_t size);
        ShiftRegister(std::initializer_list<T> values);
        ShiftRegister(const ShiftRegister& other);
        ShiftRegister(ShiftRegister&& other);

        ShiftRegister& operator=(const ShiftRegister& other);
        ShiftRegister& operator=(ShiftRegister&& other);

        void shift(const T& value);
        const T& operator[](int64_t i) const;

        const std::size_t size() const;
    };

    template<class T>
    ShiftRegister<T>::ShiftRegister(std::size_t size) : m_currentIndex(size - 1),
                                                        m_data(size)
    {
    }

    template<class T>
    ShiftRegister<T>::ShiftRegister(std::initializer_list<T> values) : m_data(values)
    {
        m_currentIndex = m_data.size() - 1;
    }

    template<class T>
    ShiftRegister<T>::ShiftRegister(const ShiftRegister& other)
        : m_currentIndex(other.m_currentIndex),
          m_data(other.m_data)
    {
    }

    template<class T>
    ShiftRegister<T>::ShiftRegister(ShiftRegister&& other)
        : m_currentIndex(other.m_currentIndex),
          m_data(std::move(other.m_data))
    {
    }

    template<class T>
    ShiftRegister<T>& ShiftRegister<T>::operator=(const ShiftRegister& other)
    {
        m_currentIndex = other.m_currentIndex;
        m_data = other.m_data;

        return *this;
    }

    template<class T>
    ShiftRegister<T>& ShiftRegister<T>::operator=(ShiftRegister&& other)
    {
        m_currentIndex = other.m_currentIndex;
        m_data = move(other.m_data);

        return *this;
    }

    template<class T>
    inline void ShiftRegister<T>::shift(const T& value)
    {
        m_currentIndex = (m_currentIndex + 1) % m_data.size();
        m_data[m_currentIndex] = value;
    }

    template<class T>
    inline const T& ShiftRegister<T>::operator[](int64_t i) const
    {
        int64_t dataIndex = (m_currentIndex - i) % static_cast<int64_t>(m_data.size());
        if (dataIndex < 0)
        {
            dataIndex += m_data.size();
        }
        return m_data[dataIndex];
    }

    template<class T>
    inline const std::size_t ShiftRegister<T>::size() const
    {
        return m_data.size();
    }
}

#endif
