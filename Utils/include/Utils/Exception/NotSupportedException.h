#ifndef UTILS_NOT_SUPPORTED_EXCEPTION_H
#define UTILS_NOT_SUPPORTED_EXCEPTION_H

#include <Utils/Exception/LoggedException.h>

#define THROW_NOT_SUPPORTED_EXCEPTION(message) \
    throw adaptone::NotSupportedException(__FILENAME__, __LOGGED_FUNCTION__, __LINE__, (message))

namespace adaptone
{
    class NotSupportedException : public LoggedException
    {
    public:
        NotSupportedException(const std::string& filename,
            const std::string& function,
            int line,
            const std::string& message);

        ~NotSupportedException() override;
    };
}

#endif
