#include <Utils/Exception/PropertyNotFoundException.h>

using namespace adaptone;
using namespace std;

PropertyNotFoundException::PropertyNotFoundException(const string& filename,
    const string& function,
    int line,
    const string& key) :
    LoggedException(filename, function, line, "PropertyNotFoundException: The property is not found (key=" + key + ")")
{
}

PropertyNotFoundException::~PropertyNotFoundException()
{
}
