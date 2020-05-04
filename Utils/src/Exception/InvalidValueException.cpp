#include <Utils/Exception/InvalidValueException.h>

using namespace adaptone;
using namespace std;

InvalidValueException::InvalidValueException(const string& filename,
    const string& function,
    int line,
    const string& key,
    const string& value) :
    LoggedException(filename, function, line,
        "InvalidValueException: The value is invalid (key=" + key + ", value=" + value + ")")
{
}

InvalidValueException::~InvalidValueException()
{
}
