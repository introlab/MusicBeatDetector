#ifndef MUSIC_BEAT_DETECTOR_UTILS_NOT_SUPPORTED_EXCEPTION_H
#define MUSIC_BEAT_DETECTOR_UTILS_NOT_SUPPORTED_EXCEPTION_H

#include <MusicBeatDetector/Utils/Exception/LoggedException.h>

#define THROW_NOT_SUPPORTED_EXCEPTION(message)                                                                         \
    throw introlab::NotSupportedException(__FILENAME__, __LOGGED_FUNCTION__, __LINE__, (message))

namespace introlab
{
    class NotSupportedException : public LoggedException
    {
    public:
        NotSupportedException(
            const std::string& filename,
            const std::string& function,
            int line,
            const std::string& message);

        ~NotSupportedException() override;
    };
}

#endif
