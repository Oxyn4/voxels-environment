// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

/**
 *  @file config.hpp
 *  @brief contains functions responsible for finding the ConfigHome directory
 *  @details Has several functions that each attempt to find ConfigHome directory using a different method. In addition to a function that calls them all in a priority order.
 */

#include "voxels/directories/base/Config.hpp"
#include "voxels/directories/base/Errors.hpp"

#include "../EnvironmentVariables.hpp"
#include "../ProgramOptions.hpp"

#include "logging.hpp"

#include <filesystem>

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

#ifndef NO_PROGRAM_OPTIONS
    using namespace boost::program_options;
#endif

namespace voxels::directories::base::config
{

    /**
     * Handles validation for Config home path candidates
     * @author Jacob evans
     * @param ConfigHome The path to validate
     * @return boost::leaf::result containing void if success or an error object
     */
    result<void> Validate(const path& ConfigHome) noexcept {
        if (not exists(ConfigHome)) {
            return new_error(DoesNotExist);
        }

        if (not is_directory(ConfigHome)) {
            return new_error(NotDirectoryError);
        }

        return {};
    }

    /**
     * Attempts to get ConfigHome value by checking environment variable VOXELS_CONFIG_HOME
     * @author Jacob evans
     * @return A boost::leaf::result containing an error object or the successfully obtained path
     */
    result<path> GetConfigHomeFromVoxels() noexcept {
        BOOST_LEAF_AUTO(const VOXELS_CONFIG_HOME, GetEnvironmentVariable("VOXELS_CONFIG_HOME"));

        BOOST_LEAF_CHECK(Validate(path(VOXELS_CONFIG_HOME)));

        return path(VOXELS_CONFIG_HOME);
    }

    /**
     * Attempts to get ConfigHome from the base directory XDG_CONFIG_HOME
     * @author Jacob evans
     * @return a boost::leaf::result containing an error object or the successfully obtained path
     */
    result<path> GetConfigHomeFromXDG() noexcept {
        BOOST_LEAF_AUTO(const XDG_CONFIG_HOME, GetEnvironmentVariable("XDG_CONFIG_HOME"));

        BOOST_LEAF_CHECK(Validate(path(XDG_CONFIG_HOME + "/voxels/")));

        return path(XDG_CONFIG_HOME + "/voxels/");
    }

    /**
     * attempts to get ConfigHome from the HOME environment variable
     * @author Jacob evans
     * @return a boost::leaf::result containing an error object or the successfully obtained path
     */
    result<path> GetConfigHomeHome() noexcept {
        BOOST_LEAF_AUTO(const HOME, GetEnvironmentVariable("HOME"));

        BOOST_LEAF_CHECK(Validate(path(HOME + "/.config/voxels/")));

        return path(HOME + "/.config/voxels/");
    }

    #ifndef NO_PROGRAM_OPTIONS
        /**
         * Uses several different Methods to determine ConfigHome
         * @author Jacob evans
         * @param VariableMap A boost::program_options::variable map to check for various flags to help determine ConfigHome
         * @return a boost::leaf::result containing the successfully obtained path or an error object indicating error.
         */
        result<path> Get(const variables_map &VariableMap) noexcept {
            #ifndef NO_LOG
                auto DirectoriesLogger = DirectoriesLoggerTag::get();
            #endif

            static result<path> ConfigHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

            if (ConfigHomeResult) {
                return ConfigHomeResult.value();
            }

            ConfigHomeResult = GetPathFromProgramOptions(VariableMap, ConfigHomeFlag);

            if (ConfigHomeResult) {
                path ConfigHome = ConfigHomeResult.value();

                #ifndef NO_LOG
                    BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found config home: '" << ConfigHome.string() <<  "' from program options flag: '" << ConfigHomeFlag << "'";
                #endif

                return ConfigHome;
            }

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine config home from program options flag: '" << ConfigHomeFlag << "'";
            #endif

            ConfigHomeResult = GetConfigHomeFromVoxels();

            if (ConfigHomeResult) {
                path ConfigHome = ConfigHomeResult.value();

                    BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'VOXELS_CONFIG_HOME'";

                return ConfigHome;
            }

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine config home from environment variable: 'VOXELS_CONFIG_HOME'";
            #endif

            ConfigHomeResult = GetConfigHomeFromXDG();

            if (ConfigHomeResult) {
                path ConfigHome = ConfigHomeResult.value();

                #ifndef NO_LOG
                    BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'XDG_CONFIG_HOME'";
                #endif

                return ConfigHome;
            }

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine config home from environment variable: 'XDG_CONFIG_HOME'";
            #endif

            ConfigHomeResult = GetConfigHomeHome();

            if (ConfigHomeResult) {
                path ConfigHome = ConfigHomeResult.value();

                #ifndef NO_LOG
                    BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'HOME'";
                #endif

                return ConfigHome;
            }

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine config home from environment variable: 'HOME'";
            #endif

            return BOOST_LEAF_NEW_ERROR(NoCandidate);
        }
    #else
        /**
        * Uses several different Methods to determine ConfigHome
        * @author Jacob Evans
        * @return a boost::leaf::result containing the successfully obtained path or an error object indicating error.
        */
        result<path> Get() noexcept {
            #ifndef NO_LOG
                auto DirectoriesLogger = DirectoriesLoggerTag::get();
            #endif

            static result<path> ConfigHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

            if (ConfigHomeResult) {
                return ConfigHomeResult.value();
            }

            ConfigHomeResult = GetConfigHomeFromVoxels();

            if (ConfigHomeResult) {
                path ConfigHome = ConfigHomeResult.value();

                    BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'VOXELS_CONFIG_HOME'";

                return ConfigHome;
            }

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine config home from environment variable: 'VOXELS_CONFIG_HOME'";
            #endif

            ConfigHomeResult = GetConfigHomeFromXDG();

            if (ConfigHomeResult) {
                path ConfigHome = ConfigHomeResult.value();

                #ifndef NO_LOG
                    BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'XDG_CONFIG_HOME'";
                #endif

                return ConfigHome;
            }

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine config home from environment variable: 'XDG_CONFIG_HOME'";
            #endif

            ConfigHomeResult = GetConfigHomeHome();

            if (ConfigHomeResult) {
                path ConfigHome = ConfigHomeResult.value();

                #ifndef NO_LOG
                    BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'HOME'";
                #endif

                return ConfigHome;
            }

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine config home from environment variable: 'HOME'";
            #endif

            return BOOST_LEAF_NEW_ERROR(NoCandidate);
        }
    #endif


}
