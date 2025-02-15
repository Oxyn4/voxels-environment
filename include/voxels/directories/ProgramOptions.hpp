#pragma once 

#include <boost/program_options.hpp>

#include <boost/leaf.hpp>

namespace Directories {
    void AddProgramOptions(boost::program_options::options_description &OptionsDescription) noexcept;
}
