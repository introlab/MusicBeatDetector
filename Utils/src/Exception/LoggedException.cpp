#include <Utils/Exception/LoggedException.h>

using namespace adaptone;
using namespace std;

LoggedException::LoggedException(const string& filename,
    const string& function,
    int line,
    const string& message) :
    runtime_error("[" + filename + ", " + function + ", " + to_string(line) + "] : " + message)
{
}

LoggedException::~LoggedException()
{
}
