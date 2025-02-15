#pragma once 

#include <boost/program_options.hpp>

#include <boost/leaf.hpp>

namespace voxels::directories {
    void AddProgramOptions(boost::program_options::options_description &OptionsDescription) noexcept;
}
