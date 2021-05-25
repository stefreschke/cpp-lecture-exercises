
#include "provider.h"

#include <sstream>

namespace provider
{


std::string providerInfo(const bool date)
{
    auto stream = std::stringstream { };

    // https://stackoverflow.com/a/33030935
#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)
    stream << STRINGIZE(PROVIDER_NAME) << std::endl;

    if (date) {
        stream << "Time: " << __TIME__ << std::endl;
        stream << "Date: " << __DATE__ << std::endl;
    }
    return stream.str();
}


}