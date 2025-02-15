#pragma once

#include <boost/leaf.hpp>

enum EnviromentVariableError {
    NotSet 
};

boost::leaf::result<std::string> GetEnvironmentVariable(const std::string &EnvironmentVariableName) noexcept; 
