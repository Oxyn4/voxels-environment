#include "EnvironmentVariables.hpp"

boost::leaf::result<std::string> GetEnvironmentVariable(const std::string &EnvironmentVariableName) noexcept {
    const char* Value = std::getenv(EnvironmentVariableName.c_str());

    if (Value == nullptr) {
        return BOOST_LEAF_NEW_ERROR(NotSet);
    } else {
    return std::string(Value);
    }
}

