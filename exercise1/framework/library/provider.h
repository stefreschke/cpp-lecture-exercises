
#pragma once

#include <string>

#ifdef PROVIDER_API_EXPORTS
    #ifdef _WIN32
        #define PROVIDER_API __attribute__((visibility("default")))
    #else
        #define PROVIDER_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _WIN32
        #define PROVIDER_API __attribute__((visibility("default")))
    #else
        #define PROVIDER_API __attribute__((visibility("default")))
    #endif
#endif

namespace provider
{


PROVIDER_API std::string providerInfo(bool date = false);


} // namespace provider
