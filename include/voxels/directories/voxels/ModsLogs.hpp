#pragma once 

#include <filesystem>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

namespace voxels::directories::voxels::mods_logs
{
    const std::string ModsLogsHomeFlag = "mods-logs-home";

    std::filesystem::path
    Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path& StateHome) noexcept;
}
