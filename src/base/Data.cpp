#include "voxels/directories/base/Data.hpp"

#include "../ProgramOptions.hpp"
#include "../EnviromentVariables.hpp"

#include "./Logging.hpp"

#include <boost/leaf/error.hpp>

namespace voxels::directories::base::data {

boost::leaf::result<void> Validate(const std::filesystem::path& DataHome) noexcept {
    if (not std::filesystem::exists(DataHome)) {
        return boost::leaf::new_error(DoesNotExist); 
    } 

    if (not std::filesystem::is_directory(DataHome)) {
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
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    static boost::leaf::result<std::filesystem::path> DataHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

    if (DataHomeResult) {
        return DataHomeResult.value();
    }
    
    DataHomeResult = GetPathFromProgramOptions(VariableMap, DataHomeFlag);

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Data home: '" << DataHome.string() <<  "' from program options flag: '" << DataHomeFlag << "'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine config home from program options flag: '" << DataHomeFlag << "'";
    #endif

    DataHomeResult = GetDataHomeFromVoxels();

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Data home: '" << DataHome.string() <<  "' from environment variable: 'VOXELS_DATA_HOME'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine data home from environment variable: 'VOXELS_DATA_DIR'";
    #endif

    DataHomeResult = GetDataHomeFromXDG();

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Data home: '" << DataHome.string() <<  "' from environment variable: 'XDG_DATA_HOME'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine data home from environment variable: 'XDG_DATA_DIR'";
    #endif

    DataHomeResult = GetDataHomeHome();

    if (DataHomeResult) {
        std::filesystem::path DataHome = DataHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Data home: '" << DataHome.string() <<  "' from environment variable: 'HOME'";
        #endif

        return DataHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine data home from environment variable: 'HOME'";
    #endif

    return BOOST_LEAF_NEW_ERROR(NoCandidate);
}
        
        }


