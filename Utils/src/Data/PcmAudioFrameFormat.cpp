#include <Utils/Data/PcmAudioFrameFormat.h>

#include <Utils/Exception/InvalidValueException.h>

#include <unordered_map>

using namespace adaptone;
using namespace std;

PcmAudioFrameFormat adaptone::parseFormat(const string& format)
{
    static const unordered_map<string, PcmAudioFrameFormat> Mapping(
        {
            { "signed_8", PcmAudioFrameFormat::Signed8 },
            { "signed_16", PcmAudioFrameFormat::Signed16 },
            { "signed_24", PcmAudioFrameFormat::Signed24 },
            { "signed_padded_24", PcmAudioFrameFormat::SignedPadded24 },
            { "signed_32", PcmAudioFrameFormat::Signed32 },

            { "unsigned_8", PcmAudioFrameFormat::Unsigned8 },
            { "unsigned_16", PcmAudioFrameFormat::Unsigned16 },
            { "unsigned_24", PcmAudioFrameFormat::Unsigned24 },
            { "unsigned_padded_24", PcmAudioFrameFormat::UnsignedPadded24 },
            { "unsigned_32", PcmAudioFrameFormat::Unsigned32 },

            { "float", PcmAudioFrameFormat::Float },
            { "double", PcmAudioFrameFormat::Double }
        });

    auto it = Mapping.find(format);
    if (it != Mapping.end())
    {
        return it->second;
    }

    THROW_INVALID_VALUE_EXCEPTION("PcmAudioFrame::Format", format);
}
