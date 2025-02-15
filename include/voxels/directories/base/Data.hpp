#pragma once

#include "Errors.hpp"

#include <boost/leaf.hpp>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

#include <filesystem>

namespace Directories {
    namespace Base {
        namespace Data {
            const std::string DataHomeFlag = "data-home";

            boost::leaf::result<std::filesystem::path> 
            GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept; 

            boost::leaf::result<void>
            Validate(const std::filesystem::path& DataHome) noexcept;
        }
    }
}


