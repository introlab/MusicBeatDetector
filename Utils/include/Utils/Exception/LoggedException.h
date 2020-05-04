#ifndef UTILS_EXCEPTION_LOGGED_EXCEPTION_H
#define UTILS_EXCEPTION_LOGGED_EXCEPTION_H

#include <stdexcept>
#include <cstring>

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

#define __LOGGED_FUNCTION__ __PRETTY_FUNCTION__

#elif defined(_MSC_VER)

#define __LOGGED_FUNCTION__ __FUNCSIG__

#endif

#define __FILENAME__ (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define THROW_LOGGED_EXCEPTION(message) \
    throw adaptone::LoggedException(__FILENAME__, __LOGGED_FUNCTION__, __LINE__, (message))

namespace adaptone
{
    class LoggedException : public std::runtime_error
    {
    public:
        LoggedException(const std::string& filename, const std::string& function, int line, const std::string& message);
        ~LoggedException() override;
    };
}

#endif
