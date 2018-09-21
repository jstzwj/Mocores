#ifndef MOCORES_COMMON_UTIL_PLATFORM_INFO_H
#define MOCORES_COMMON_UTIL_PLATFORM_INFO_H

#include <boost/thread.hpp>

namespace mocores
{
    inline int hardware_concurrency()
    {
        return boost::thread::hardware_concurrency();
    }

}

#endif