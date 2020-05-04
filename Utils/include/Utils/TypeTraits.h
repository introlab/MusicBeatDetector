#ifndef UTILS_TYPE_TRAITS_H
#define UTILS_TYPE_TRAITS_H

#include <type_traits>

namespace adaptone
{
    template<class T>
    struct AlwaysFalse : std::false_type
    {
    };

    template<class T>
    struct IsReturningBool : std::false_type
    {
    };

    template<class ... Types>
    struct IsReturningBool<bool(Types...)> : std::true_type
    {
    };
}

#endif
