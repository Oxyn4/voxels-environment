#pragma once

#include <boost/leaf.hpp>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

#include <filesystem>

#include "Errors.hpp"

namespace voxels::directories::base::state
{
    const std::string StateHomeFlag = "state-home";
            
    boost::leaf::result<std::filesystem::path>
    Get(const boost::program_options::variables_map &VariableMap) noexcept;


}
