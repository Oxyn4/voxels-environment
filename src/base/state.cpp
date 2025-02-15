// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

#include "voxels/directories/base/State.hpp"

#include "../EnvironmentVariables.hpp"
#include "../ProgramOptions.hpp"

#include "logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::base::state {

result<void> Validate(const path& StateHome) noexcept {
    if (not exists(StateHome)) {
        return new_error(DoesNotExist);
    } 

    if (not is_directory(StateHome)) {
        return new_error(NotDirectoryError);
    }

    return {};
}

result<path> GetStateHomeFromVoxels() noexcept {
    BOOST_LEAF_AUTO(const VOXELS_State_HOME, GetEnvironmentVariable("VOXELS_STATE_HOME"));

    BOOST_LEAF_CHECK(Validate(std::filesystem::path(VOXELS_State_HOME)));

    return path(VOXELS_State_HOME);
}

result<path> GetStateHomeFromXDG() noexcept {
    BOOST_LEAF_AUTO(const XDG_State_HOME, GetEnvironmentVariable("XDG_STATE_HOME"));
    
    BOOST_LEAF_CHECK(Validate(std::filesystem::path(XDG_State_HOME + "/voxels/")));

    return path(XDG_State_HOME + "/voxels/");
}

result<path> GetStateHomeHome() noexcept {
    BOOST_LEAF_AUTO(const HOME, GetEnvironmentVariable("HOME"));
    
    BOOST_LEAF_CHECK(Validate(std::filesystem::path(HOME + "/.local/state/voxels/")));
    
    return path(HOME + "/.local/state/voxels/");
}


// base XDG specified directories 
result<path> Get(const variables_map &VariableMap) noexcept {
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    static result<path> StateHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

    if (StateHomeResult) {
        return StateHomeResult.value();
    }

    StateHomeResult = GetPathFromProgramOptions(VariableMap, StateHomeFlag);

    if (StateHomeResult) {
        path StateHome = StateHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found State home: '" << StateHome.string() <<  "' from program options flag: '" << StateHomeFlag << "'";
        #endif

        return StateHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine config home from program options flag: '" << StateHomeFlag << "'";
    #endif


    StateHomeResult = GetStateHomeFromVoxels();

    if (StateHomeResult) {
        path StateHome = StateHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'VOXELS_STATE_HOME'";
        #endif

        return StateHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine state home from environment variable: 'VOXELS_STATE_HOME'";
    #endif

    StateHomeResult = GetStateHomeFromXDG();

    if (StateHomeResult) {
        path StateHome = StateHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger, trace) << "Found State home: '" << StateHome.string() <<  "' from environment variable: 'XDG_STATE_HOME'";
        #endif

        return StateHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger, warning) << "Could not determine state home from environment variable: 'XDG_STATE_HOME'";
    #endif

    StateHomeResult = GetStateHomeHome();

    if (StateHomeResult) {
        path StateHome = StateHomeResult.value();

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
