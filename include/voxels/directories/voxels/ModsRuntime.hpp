// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

/**
 * @file ModsRuntime.hpp
 * @author Jacob Evans
 * @brief This header contains definitions for the mods runtime directory related functionality
 */

#pragma once

#include <filesystem>

#include <boost/program_options.hpp>

#include <boost/log/trivial.hpp>


/**
 * @namespace voxels::directories::voxels::mods_runtime
 * @brief This namespace contains definitions related to the mods runtime directory functionality
 */
namespace voxels::directories::voxels::mods_runtime
{
    const std::string ModsRuntimeFlag = "mods-runtime";

    std::filesystem::path
    Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path& RuntimeHome) noexcept;
}
