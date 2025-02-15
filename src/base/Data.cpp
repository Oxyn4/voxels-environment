#include "voxel-directories/base/Data.hpp"

#include "../ProgramOptions.hpp"
#include "../EnviromentVariables.hpp"

namespace Directories {
    namespace Base {
        namespace Data {

boost::leaf::result<void> Validate(std::filesystem::path& DataHome) noexcept {

}

boost::leaf::result<std::filesystem::path> GetDataHomeFromVoxels() noexcept {
    BOOST_LEAF_AUTO(VOXELS_Data_HOME, GetEnviromentVariable("VOXELS_DATA_HOME"));

    return std::filesystem::path(VOXELS_Data_HOME);
}

boost::leaf::result<std::filesystem::path> GetDataHomeFromXDG() noexcept {
    BOOST_LEAF_AUTO(XDG_Data_HOME, GetEnviromentVariable("XDG_DATA_HOME"));

    return std::filesystem::path(XDG_Data_HOME + "/voxels/");
}

boost::leaf::result<std::filesystem::path> GetDataHomeHome() noexcept {
    BOOST_LEAF_AUTO(HOME, GetEnviromentVariable("HOME"));
    
    return std::filesystem::path(HOME + "/.local/share/voxels");
}

// base XDG specified directories 
boost::leaf::result<std::filesystem::path> GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept {
    static boost::leaf::result<std::filesystem::path> DataHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

    if (DataHomeResult) {
        return DataHomeResult.value();
    }
    
    DataHomeResult = GetPathFromProgramOptions(VariableMap, DataHomeFlag);

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found Data home: '" << DataHome.string() <<  "' from program options flag: '" << DataHomeFlag << "'";
        
        return DataHome;
    }

    BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from program options flag: '" << DataHomeFlag << "'";

    DataHomeResult = GetDataHomeFromVoxels();

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found Data home: '" << DataHome.string() <<  "' from enviroment variable: 'VOXELS_DATA_HOME'";
        
        return DataHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine data home from enviroment variable: 'VOXELS_DATA_DIR'";

    DataHomeResult = GetDataHomeFromXDG();

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found Data home: '" << DataHome.string() <<  "' from enviroment variable: 'XDG_DATA_HOME'";
        
        return DataHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine data home from enviroment variable: 'XDG_DATA_DIR'";

    DataHomeResult = GetDataHomeHome();

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found Data home: '" << DataHome.string() <<  "' from enviroment variable: 'HOME'";
        
        return DataHome;
    }

    BOOST_LOG_TRIVIAL(warning) << "Could not determine data home from enviroment variable: 'HOME'";

    return BOOST_LEAF_NEW_ERROR(NoCandidate);
}
        
        }
    }
}
