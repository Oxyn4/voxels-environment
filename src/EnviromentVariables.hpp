#pragma once

#include <boost/leaf.hpp>

enum EnvironmentVariableError {
    NotSet 
};

boost::leaf::result<std::string> GetEnvironmentVariable(const std::string &EnvironmentVariableName) noexcept; 
