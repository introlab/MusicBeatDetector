#ifndef UTILS_EXCEPTION_PROPERTY_PARSE_EXCEPTION_H
#define UTILS_EXCEPTION_PROPERTY_PARSE_EXCEPTION_H

#include <Utils/Exception/LoggedException.h>

#define THROW_PROPERTY_PARSE_EXCEPTION(key, value) \
    throw adaptone::PropertyParseException(__FILENAME__, __LOGGED_FUNCTION__, __LINE__, (key), (value))

namespace adaptone
{
    class PropertyParseException : public LoggedException
    {
    public:
        PropertyParseException(const std::string& filename,
            const std::string& function,
            int line,
            const std::string& key,
            const std::string& value);

        ~PropertyParseException() override;
    };
}

#endif
