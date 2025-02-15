#pragma once

#include <boost/program_options.hpp>

#include <boost/leaf.hpp>

#include <filesystem>

enum ProgramOptionError {
    NotPresent,
};

boost::leaf::result<std::filesystem::path> GetPathFromProgramOptions(const boost::program_options::variables_map& VariableMap, const std::string& Flag) noexcept;
