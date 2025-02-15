#pragma once

#include <boost/leaf.hpp>

enum EnviromentVariableError {
    NotSet 
};

boost::leaf::result<std::string> GetEnviromentVariable(const std::string &EnviromentVariableName) noexcept; 
