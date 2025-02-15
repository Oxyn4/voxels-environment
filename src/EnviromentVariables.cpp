#include "EnviromentVariables.hpp"

boost::leaf::result<std::string> GetEnviromentVariable(const std::string &EnviromentVariableName) noexcept {
    const char* Value = std::getenv(EnviromentVariableName.c_str());

    if (Value == NULL) {
        return BOOST_LEAF_NEW_ERROR(NotSet);
    } else {
    return std::string(Value);
    }
}

