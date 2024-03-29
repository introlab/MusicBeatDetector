#ifndef MUSIC_BEAT_DETECTOR_UTILS_INVALID_VALUE_EXCEPTION_H
#define MUSIC_BEAT_DETECTOR_UTILS_INVALID_VALUE_EXCEPTION_H

#include <MusicBeatDetector/Utils/Exception/LoggedException.h>

#define THROW_INVALID_VALUE_EXCEPTION(key, value)                                                                      \
    throw introlab::InvalidValueException(__FILENAME__, __LOGGED_FUNCTION__, __LINE__, (key), (value))

namespace introlab
{
    class InvalidValueException : public LoggedException
    {
    public:
        InvalidValueException(
            const std::string& filename,
            const std::string& function,
            int line,
            const std::string& name,
            const std::string& value);

        ~InvalidValueException() override;
    };
}

#endif
