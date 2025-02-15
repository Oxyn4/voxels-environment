#include "voxels/directories/base/State.hpp"

#include "../EnvironmentVariables.hpp"
#include "../ProgramOptions.hpp"

#include "Logging.hpp"


namespace voxels::directories::base::state {

boost::leaf::result<void> Validate(const std::filesystem::path& StateHome) noexcept {
    if (not std::filesystem::exists(StateHome)) {
        return boost::leaf::new_error(DoesNotExist); 
    } 

    if (not std::filesystem::is_directory(StateHome)) {
        return boost::leaf::new_error(NotDirectoryError);
    }

    return {};
}

boost::leaf::result<std::filesystem::path> GetStateHomeFromVoxels() noexcept {
    BOOST_LEAF_AUTO(const VOXELS_State_HOME, GetEnvironmentVariable("VOXELS_STATE_HOME"));

    BOOST_LEAF_CHECK(Validate(std::filesystem::path(VOXELS_State_HOME)));

    return std::filesystem::path(VOXELS_State_HOME);
}

boost::leaf::result<std::filesystem::path> GetStateHomeFromXDG() noexcept {
    BOOST_LEAF_AUTO(const XDG_State_HOME, GetEnvironmentVariable("XDG_STATE_HOME"));
    
    BOOST_LEAF_CHECK(Validate(std::filesystem::path(XDG_State_HOME + "/voxels/")));

    return std::filesystem::path(XDG_State_HOME + "/voxels/");
}

boost::leaf::result<std::filesystem::path> GetStateHomeHome() noexcept {
    BOOST_LEAF_AUTO(const HOME, GetEnvironmentVariable("HOME"));
    
    BOOST_LEAF_CHECK(Validate(std::filesystem::path(HOME + "/.local/state/voxels/")));
    
    return std::filesystem::path(HOME + "/.local/state/voxels/");
}


// base XDG specified directories 
boost::leaf::result<std::filesystem::path> GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept {
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    static boost::leaf::result<std::filesystem::path> StateHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

    if (StateHomeResult) {
        return StateHomeResult.value();
    }

    StateHomeResult = GetPathFromProgramOptions(VariableMap, StateHomeFlag);

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found State home: '" << StateHome.string() <<  "' from program options flag: '" << StateHomeFlag << "'";
        #endif

        return StateHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine config home from program options flag: '" << StateHomeFlag << "'";
    #endif


    StateHomeResult = GetStateHomeFromVoxels();

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'VOXELS_STATE_HOME'";
        #endif

        return StateHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine state home from environment variable: 'VOXELS_STATE_HOME'";
    #endif

    StateHomeResult = GetStateHomeFromXDG();

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'XDG_STATE_HOME'";
        #endif

        return StateHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine state home from environment variable: 'XDG_STATE_HOME'";
    #endif

    StateHomeResult = GetStateHomeHome();

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        #ifndef NO_LOG
             BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'HOME'";
        #endif

        return StateHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine state home from environment variable: 'HOME'";
    #endif

    return BOOST_LEAF_NEW_ERROR(NoCandidate);
}
        
}
