#include "voxels/directories/base/Data.hpp"

#include "../ProgramOptions.hpp"
#include "../EnvironmentVariables.hpp"

#include "./Logging.hpp"

#include <boost/leaf/error.hpp>

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::base::data {

result<void> Validate(const path& DataHome) noexcept {
    if (not exists(DataHome)) {
        return new_error(DoesNotExist);
    } 

    if (not is_directory(DataHome)) {
        return new_error(NotDirectoryError);
    }

    return {};
}

result<path> GetDataHomeFromVoxels() noexcept {
    BOOST_LEAF_AUTO(const VOXELS_Data_HOME, GetEnvironmentVariable("VOXELS_DATA_HOME"));

    BOOST_LEAF_CHECK(Validate(path(VOXELS_Data_HOME)));

    return path(VOXELS_Data_HOME);
}

result<path> GetDataHomeFromXDG() noexcept {
    BOOST_LEAF_AUTO(const XDG_Data_HOME, GetEnvironmentVariable("XDG_DATA_HOME"));

    BOOST_LEAF_CHECK(Validate(path(XDG_Data_HOME + "/voxels/")));
    
    return path(XDG_Data_HOME + "/voxels/");
}

result<path> GetDataHomeHome() noexcept {
    BOOST_LEAF_AUTO(const HOME, GetEnvironmentVariable("HOME"));
    
    BOOST_LEAF_CHECK(Validate(path(HOME + "/.local/share/voxels")));
    
    return path(HOME + "/.local/share/voxels");
}

// base XDG specified directories 
result<path> Get(const variables_map &VariableMap) noexcept {
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    static result<path> DataHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

    if (DataHomeResult) {
        return DataHomeResult.value();
    }
    
    DataHomeResult = GetPathFromProgramOptions(VariableMap, DataHomeFlag);

    if (DataHomeResult) {
        path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found Data home: '" << DataHome.string() <<  "' from program options flag: '" << DataHomeFlag << "'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine config home from program options flag: '" << DataHomeFlag << "'";
    #endif

    DataHomeResult = GetDataHomeFromVoxels();

    if (DataHomeResult) {
        path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found Data home: '" << DataHome.string() <<  "' from environment variable: 'VOXELS_DATA_HOME'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine data home from environment variable: 'VOXELS_DATA_DIR'";
    #endif

    DataHomeResult = GetDataHomeFromXDG();

    if (DataHomeResult) {
        path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found Data home: '" << DataHome.string() <<  "' from environment variable: 'XDG_DATA_HOME'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine data home from environment variable: 'XDG_DATA_DIR'";
    #endif

    DataHomeResult = GetDataHomeHome();

    if (DataHomeResult) {
        path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found Data home: '" << DataHome.string() <<  "' from environment variable: 'HOME'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine data home from environment variable: 'HOME'";
    #endif

    return BOOST_LEAF_NEW_ERROR(NoCandidate);
}
        
        }


