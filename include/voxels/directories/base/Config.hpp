#pragma once

#include <boost/leaf.hpp>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

#include <filesystem>

#include "Errors.hpp"

namespace voxels::directories::base::config
{
    const std::string ConfigHomeFlag = "config-home";

    boost::leaf::result<std::filesystem::path>
    GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept;
}


