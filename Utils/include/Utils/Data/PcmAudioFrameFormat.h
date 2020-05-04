#ifndef UTILS_DATA_PCM_AUDIO_FRAME_FORMAT_H
#define UTILS_DATA_PCM_AUDIO_FRAME_FORMAT_H

#include <string>
#include <cstddef>

namespace adaptone
{
    enum class PcmAudioFrameFormat : std::size_t
    {
        Signed8 = 1,
        Signed16 = 2,
        Signed24 = 3,
        SignedPadded24 = 4 + 64,
        Signed32 = 4,

        Unsigned8 = 1 + 16,
        Unsigned16 = 2 + 16,
        Unsigned24 = 3 + 16,
        UnsignedPadded24 = 4 + 16 + 64,
        Unsigned32 = 4 + 16,

        Float = 4 + 32,
        Double = 8 + 32
    };

    inline std::size_t formatSize(PcmAudioFrameFormat format)
    {
        return static_cast<std::size_t>(format) & 0b1111;
    }

    inline std::size_t size(PcmAudioFrameFormat format, std::size_t channelCount, std::size_t sampleCount)
    {
        return channelCount * sampleCount * formatSize(format);
    }

    PcmAudioFrameFormat parseFormat(const std::string& format);
}

#endif
