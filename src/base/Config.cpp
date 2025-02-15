#include "voxels/directories/base/Config.hpp"
#include "voxels/directories/base/Errors.hpp"

#include "../EnvironmentVariables.hpp"
#include "../ProgramOptions.hpp"

#include "Logging.hpp"

#include <filesystem>

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::base::config
{

    result<void> Validate(const path& ConfigHome) noexcept {
        if (not exists(ConfigHome)) {
            return new_error(DoesNotExist);
        }

        if (not is_directory(ConfigHome)) {
            return new_error(NotDirectoryError);
        }

        return {};
    }

    result<path> GetConfigHomeFromVoxels() noexcept {
        BOOST_LEAF_AUTO(const VOXELS_CONFIG_HOME, GetEnvironmentVariable("VOXELS_CONFIG_HOME"));

        BOOST_LEAF_CHECK(Validate(path(VOXELS_CONFIG_HOME)));

        return path(VOXELS_CONFIG_HOME);
    }

    result<path> GetConfigHomeFromXDG() noexcept {
        BOOST_LEAF_AUTO(const XDG_CONFIG_HOME, GetEnvironmentVariable("XDG_CONFIG_HOME"));

        BOOST_LEAF_CHECK(Validate(path(XDG_CONFIG_HOME + "/voxels/")));

        return path(XDG_CONFIG_HOME + "/voxels/");
    }

    result<path> GetConfigHomeHome() noexcept {
        BOOST_LEAF_AUTO(const HOME, GetEnvironmentVariable("HOME"));

        BOOST_LEAF_CHECK(Validate(path(HOME + "/.config/voxels/")));

        return path(HOME + "/.config/voxels/");
    }

    // base XDG specified directories
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


}
