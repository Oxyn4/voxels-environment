#include "voxel-directories/base/Config.hpp"

#include "../EnviromentVariables.hpp"

#include "../ProgramOptions.hpp"

namespace Directories {
    namespace Base {
        namespace Config {

boost::leaf::result<void> Validate(std::filesystem::path& ConfigHome) noexcept {}

boost::leaf::result<std::filesystem::path> GetConfigHomeFromVoxels() noexcept {
    BOOST_LEAF_AUTO(VOXELS_CONFIG_HOME, GetEnviromentVariable("VOXELS_CONFIG_HOME"));

    return std::filesystem::path(VOXELS_CONFIG_HOME);
}

boost::leaf::result<std::filesystem::path> GetConfigHomeFromXDG() noexcept {
    BOOST_LEAF_AUTO(XDG_CONFIG_HOME, GetEnviromentVariable("XDG_CONFIG_HOME"));

    return std::filesystem::path(XDG_CONFIG_HOME + "/voxels/");
}

boost::leaf::result<std::filesystem::path> GetConfigHomeHome() noexcept {
    BOOST_LEAF_AUTO(HOME, GetEnviromentVariable("HOME"));
    
    return std::filesystem::path(HOME + "/.config/voxels/");
}

// base XDG specified directories 
boost::leaf::result<std::filesystem::path> GetCandiates(const boost::program_options::variables_map &VariableMap) noexcept {
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

        BOOST_LOG_TRIVIAL(trace) << "Found config home: '" << ConfigHome.string() <<  "' from enviroment variable: 'VOXELS_CONFIG_HOME'";
        
        return ConfigHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from enviroment variable: 'VOXELS_CONFIG_HOME'";

    ConfigHomeResult = GetConfigHomeFromXDG();

    if (ConfigHomeResult) {
        std::filesystem::path ConfigHome = ConfigHomeResult.value();
 
        BOOST_LOG_TRIVIAL(trace) << "Found config home: '" << ConfigHome.string() <<  "' from enviroment variable: 'XDG_CONFIG_HOME'";
        
        return ConfigHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from enviroment variable: 'XDG_CONFIG_HOME'";

    ConfigHomeResult = GetConfigHomeHome();

    if (ConfigHomeResult) {
        std::filesystem::path ConfigHome = ConfigHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found config home: '" << ConfigHome.string() <<  "' from enviroment variable: 'HOME'";
        
        return ConfigHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from enviroment variable: 'HOME'";

    return BOOST_LEAF_NEW_ERROR(NoCandidate);
}


        }
    }
}
