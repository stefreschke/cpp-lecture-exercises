
#include "provider.h"

#include <sstream>


// TODO: pass PROVIDER_NAME using compiler options


namespace provider
{


std::string providerInfo(const bool date)
{
    auto stream = std::stringstream { };

    // TODO: output provider name using the PROVIDER_NAME defined for compilation

    // TODO: if date is true, output the date of compilation as well using predefined c++ macros
    
    return stream.str();
}


}