#include "voxels/directories/base/State.hpp"

#include "../EnviromentVariables.hpp"
#include "../ProgramOptions.hpp"



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
    static boost::leaf::result<std::filesystem::path> StateHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

    if (StateHomeResult) {
        return StateHomeResult.value();
    }

    StateHomeResult = GetPathFromProgramOptions(VariableMap, StateHomeFlag);

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found State home: '" << StateHome.string() <<  "' from program options flag: '" << StateHomeFlag << "'";
        
        return StateHome;
    }

    BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from program options flag: '" << StateHomeFlag << "'";


    StateHomeResult = GetStateHomeFromVoxels();

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'VOXELS_STATE_HOME'";
        
        return StateHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine state home from environment variable: 'VOXELS_STATE_HOME'";

    StateHomeResult = GetStateHomeFromXDG();

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'XDG_STATE_HOME'";
        
        return StateHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine state home from environment variable: 'XDG_STATE_HOME'";

    StateHomeResult = GetStateHomeHome();

    if (StateHomeResult) {
        std::filesystem::path StateHome = StateHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'HOME'";
        
        return StateHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine state home from environment variable: 'HOME'";

    return BOOST_LEAF_NEW_ERROR(NoCandidate);
}
        
}
