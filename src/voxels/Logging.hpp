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