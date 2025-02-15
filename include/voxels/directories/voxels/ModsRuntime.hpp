#pragma once 

#include <filesystem>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

namespace Directories {
    namespace Voxels {
        namespace ModsRuntime {
            const std::string ModsRuntimeFlag = "mods-runtime";

            std::filesystem::path 
            Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path& RuntimeHome) noexcept;
        }
    }
}
