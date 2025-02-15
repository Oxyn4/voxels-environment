#pragma once 

#include <filesystem>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

namespace Directories {
    namespace Voxels {
        namespace Mods {
            const std::string ModsHomeFlag = "mods-home";

            std::filesystem::path 
            Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path& DataHome) noexcept;
        }
    }
}
