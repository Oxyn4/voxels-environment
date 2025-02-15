#include "voxels/directories/base/Config.hpp"

#include "../EnviromentVariables.hpp"

#include "../ProgramOptions.hpp"

#include "voxels/directories/base/Errors.hpp"

#include <filesystem>

namespace Directories::Base::Config
{

    boost::leaf::result<void> Validate(const std::filesystem::path& ConfigHome) noexcept {
        if (!std::filesystem::exists(ConfigHome)) {
            return boost::leaf::new_error(DoesNotExist);
        }

        if (std::filesystem::is_directory(ConfigHome)) {
            return boost::leaf::new_error(NotDirectoryError);
        }

        return {};
    }

    boost::leaf::result<std::filesystem::path> GetConfigHomeFromVoxels() noexcept {
        BOOST_LEAF_AUTO(const VOXELS_CONFIG_HOME, GetEnvironmentVariable("VOXELS_CONFIG_HOME"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path(VOXELS_CONFIG_HOME)));

        return std::filesystem::path(VOXELS_CONFIG_HOME);
    }

    boost::leaf::result<std::filesystem::path> GetConfigHomeFromXDG() noexcept {
        BOOST_LEAF_AUTO(const XDG_CONFIG_HOME, GetEnvironmentVariable("XDG_CONFIG_HOME"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path(XDG_CONFIG_HOME + "/voxels/")));

        return std::filesystem::path(XDG_CONFIG_HOME + "/voxels/");
    }

    boost::leaf::result<std::filesystem::path> GetConfigHomeHome() noexcept {
        BOOST_LEAF_AUTO(const HOME, GetEnvironmentVariable("HOME"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path(HOME + "/.config/voxels/")));

        return std::filesystem::path(HOME + "/.config/voxels/");
    }

    // base XDG specified directories
    boost::leaf::result<std::filesystem::path> GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept {
        static boost::leaf::result<std::filesystem::path> ConfigHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

        if (ConfigHomeResult) {
            return ConfigHomeResult.value();
        }

        ConfigHomeResult = GetPathFromProgramOptions(VariableMap, ConfigHomeFlag);

        if (ConfigHomeResult) {
            std::filesystem::path ConfigHome = ConfigHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found config home: '" << ConfigHome.string() <<  "' from program options flag: '" << ConfigHomeFlag << "'";

            return ConfigHome;
        }

        BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from program options flag: '" << ConfigHomeFlag << "'";

        ConfigHomeResult = GetConfigHomeFromVoxels();

        if (ConfigHomeResult) {
            std::filesystem::path ConfigHome = ConfigHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'VOXELS_CONFIG_HOME'";

            return ConfigHome;
        }

        BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from environment variable: 'VOXELS_CONFIG_HOME'";

        ConfigHomeResult = GetConfigHomeFromXDG();

        if (ConfigHomeResult) {
            std::filesystem::path ConfigHome = ConfigHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'XDG_CONFIG_HOME'";

            return ConfigHome;
        }

        BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from environment variable: 'XDG_CONFIG_HOME'";

        ConfigHomeResult = GetConfigHomeHome();

        if (ConfigHomeResult) {
            std::filesystem::path ConfigHome = ConfigHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found config home: '" << ConfigHome.string() <<  "' from environment variable: 'HOME'";

            return ConfigHome;
        }

        BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from environment variable: 'HOME'";

        return BOOST_LEAF_NEW_ERROR(NoCandidate);
    }


}
