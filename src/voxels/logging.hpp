// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

#include <boost/utility/identity_type.hpp>

#ifndef NO_LOG
    BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(
        DirectoriesLoggerTag,
        BOOST_IDENTITY_TYPE((boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level, std::string>)),
        (boost::log::keywords::channel = "voxels::directories::voxels")
    )
#endif