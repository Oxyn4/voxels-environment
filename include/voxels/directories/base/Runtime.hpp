#pragma once

#include <boost/leaf.hpp>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>

#include "Errors.hpp"

#include <filesystem>

namespace Directories {
    namespace Base {
        namespace Runtime {
            const std::string RuntimeHomeFlag = "runtime-home";

            boost::leaf::result<std::filesystem::path> 
            GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept;
        }
    }
}
