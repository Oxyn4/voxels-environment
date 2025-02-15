#include "voxels/directories/base/Data.hpp"

#include "../ProgramOptions.hpp"
#include "../EnviromentVariables.hpp"

#include <boost/leaf/error.hpp>



namespace Directories::Base::Data {

boost::leaf::result<void> Validate(std::filesystem::path DataHome) noexcept {
    if (!std::filesystem::exists(DataHome)) { 
        return boost::leaf::new_error(DoesNotExist); 
    } 

    if (std::filesystem::is_directory(DataHome)) {
        return boost::leaf::new_error(NotDirectoryError);
    }

    return {};
}

boost::leaf::result<std::filesystem::path> GetDataHomeFromVoxels() noexcept {
    BOOST_LEAF_AUTO(const VOXELS_Data_HOME, GetEnvironmentVariable("VOXELS_DATA_HOME"));

    BOOST_LEAF_CHECK(Validate(std::filesystem::path(VOXELS_Data_HOME)));

    return std::filesystem::path(VOXELS_Data_HOME);
}

boost::leaf::result<std::filesystem::path> GetDataHomeFromXDG() noexcept {
    BOOST_LEAF_AUTO(const XDG_Data_HOME, GetEnvironmentVariable("XDG_DATA_HOME"));

    BOOST_LEAF_CHECK(Validate(std::filesystem::path(XDG_Data_HOME + "/voxels/")));
    
    return std::filesystem::path(XDG_Data_HOME + "/voxels/");
}

boost::leaf::result<std::filesystem::path> GetDataHomeHome() noexcept {
    BOOST_LEAF_AUTO(const HOME, GetEnvironmentVariable("HOME"));
    
    BOOST_LEAF_CHECK(Validate(std::filesystem::path(HOME + "/.local/share/voxels")));
    
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


