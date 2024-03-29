#ifndef MUSIC_BEAT_DETECTOR_UTILS_EXCEPTION_PROPERTY_PARSE_EXCEPTION_H
#define MUSIC_BEAT_DETECTOR_UTILS_EXCEPTION_PROPERTY_PARSE_EXCEPTION_H

#include <MusicBeatDetector/Utils/Exception/LoggedException.h>

#define THROW_PROPERTY_PARSE_EXCEPTION(key, value)                                                                     \
    throw introlab::PropertyParseException(__FILENAME__, __LOGGED_FUNCTION__, __LINE__, (key), (value))

namespace introlab
{
    class PropertyParseException : public LoggedException
    {
    public:
        PropertyParseException(
            const std::string& filename,
            const std::string& function,
            int line,
            const std::string& key,
            const std::string& value);

        ~PropertyParseException() override;
    };
}

#endif
