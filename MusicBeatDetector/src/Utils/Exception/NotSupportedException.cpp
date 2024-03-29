#include <MusicBeatDetector/Utils/Exception/NotSupportedException.h>

using namespace introlab;
using namespace std;

NotSupportedException::NotSupportedException(
    const string& filename,
    const string& function,
    int line,
    const string& message)
    : LoggedException(filename, function, line, "NotSupportedException: " + message)
{
}

NotSupportedException::~NotSupportedException() {}
