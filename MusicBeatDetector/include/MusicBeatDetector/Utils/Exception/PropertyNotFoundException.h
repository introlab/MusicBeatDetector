#ifndef MUSIC_BEAT_DETECTOR_UTILS_EXCEPTION_PROPERTY_NOT_FOUND_EXCEPTION_H
#define MUSIC_BEAT_DETECTOR_UTILS_EXCEPTION_PROPERTY_NOT_FOUND_EXCEPTION_H

#include <MusicBeatDetector/Utils/Exception/LoggedException.h>

#define THROW_PROPERTY_NOT_FOUND_EXCEPTION(key)                                                                        \
    throw introlab::PropertyNotFoundException(__FILENAME__, __LOGGED_FUNCTION__, __LINE__, (key))

namespace introlab
{
    class PropertyNotFoundException : public LoggedException
    {
    public:
        PropertyNotFoundException(
            const std::string& filename,
            const std::string& function,
            int line,
            const std::string& key);

        ~PropertyNotFoundException() override;
    };
}

#endif
