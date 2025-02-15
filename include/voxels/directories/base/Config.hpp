#pragma once

#include <boost/leaf.hpp>

#ifndef NO_PROGRAM_OPTIONS
    #include <boost/program_options.hpp>
#endif

#include <boost/log/trivial.hpp>

#include <filesystem>

#include "Errors.hpp"

namespace voxels::directories::base::config
{
    const std::string ConfigHomeFlag = "config-home";

    #ifndef NO_PROGRAM_OPTIONS
        boost::leaf::result<std::filesystem::path> Get(const boost::program_options::variables_map &VariableMap) noexcept;
    #else
        boost::leaf::result<std::filesystem::path> Get() noexcept;
    #endif
}


