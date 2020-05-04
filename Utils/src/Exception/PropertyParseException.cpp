#include <Utils/Exception/PropertyParseException.h>

using namespace adaptone;
using namespace std;

PropertyParseException::PropertyParseException(const string& filename,
    const string& function,
    int line,
    const string& key,
    const string& value) :
    LoggedException(filename, function, line,
        "PropertyParseException: The property cannot be parsed (key=" + key + ", value=" + value + ")")
{
}

PropertyParseException::~PropertyParseException()
{
}
