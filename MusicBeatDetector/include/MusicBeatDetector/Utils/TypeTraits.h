#ifndef MUSIC_BEAT_DETECTOR_UTILS_TYPE_TRAITS_H
#define MUSIC_BEAT_DETECTOR_UTILS_TYPE_TRAITS_H

#include <type_traits>

namespace introlab
{
    template<class T>
    struct AlwaysFalse : std::false_type
    {
    };

    template<class T>
    struct IsReturningBool : std::false_type
    {
    };

    template<class... Types>
    struct IsReturningBool<bool(Types...)> : std::true_type
    {
    };
}

#endif
