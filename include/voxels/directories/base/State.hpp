// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

/**
 * @file Runtime.hpp
 * @author Jacob Evans
 * @brief This header contains definitions for the State directory related functionality
 */

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
