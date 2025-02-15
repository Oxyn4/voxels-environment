// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

#include "EnvironmentVariables.hpp"

boost::leaf::result<std::string> GetEnvironmentVariable(const std::string &EnvironmentVariableName) noexcept {
    const char* Value = std::getenv(EnvironmentVariableName.c_str());

    if (Value == nullptr) {
        return BOOST_LEAF_NEW_ERROR(NotSet);
    } else {
    return std::string(Value);
    }
}

