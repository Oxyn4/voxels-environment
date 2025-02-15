#pragma once

#include <boost/leaf.hpp>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

#include <filesystem>

#include "Errors.hpp"

namespace Directories {
    namespace Base {
        namespace State {
            const std::string StateHomeFlag = "state-home";
            
            boost::leaf::result<std::filesystem::path> 
            GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept;

            boost::leaf::result<void> 
            Validate(const std::filesystem::path& StateHome) noexcept;
        
        }
    }
}
