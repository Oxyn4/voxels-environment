#pragma once

#include "Errors.hpp"

#include <boost/leaf.hpp>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

#include <filesystem>

namespace voxels::directories::base::data
{
    const std::string DataHomeFlag = "data-home";

    boost::leaf::result<std::filesystem::path>
    GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept;

}


