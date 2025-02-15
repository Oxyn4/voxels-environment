#pragma once

#include <boost/leaf.hpp>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

#include <filesystem>

#include "Errors.hpp"

namespace Directories {
    namespace Base {
        namespace Config {
            const std::string ConfigHomeFlag = "config-home";
            
            boost::leaf::result<void> 
            Validate(const std::filesystem::path& ConfigHome) noexcept;

            boost::leaf::result<std::filesystem::path> 
            GetCandiates(const boost::program_options::variables_map &VariableMap) noexcept;
        }
    }
}


