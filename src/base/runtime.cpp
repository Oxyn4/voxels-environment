// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

// public interface
#include "voxels/directories/base/Runtime.hpp"

#include "../EnvironmentVariables.hpp"
#include "../ProgramOptions.hpp"

#include <boost/leaf/error.hpp>

#include "logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::base::runtime
{

    result<void> Validate(const path& RuntimeHome) noexcept {
        if (not exists(RuntimeHome)) {
            return new_error(DoesNotExist);
        }

        if (not is_directory(RuntimeHome)) {
            return new_error(NotDirectoryError);
        }

        return {};
    }

    result<path> GetRuntimeHomeFromVoxels() noexcept {
        BOOST_LEAF_AUTO(const VOXELS_Runtime_HOME, GetEnvironmentVariable("VOXELS_RUNTIME_HOME"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((VOXELS_Runtime_HOME))));

        return path(VOXELS_Runtime_HOME);
    }

    result<path> GetRuntimeHomeFromXDG() noexcept {
        BOOST_LEAF_AUTO(const XDG_Runtime_HOME, GetEnvironmentVariable("XDG_RUNTIME_DIR"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((XDG_Runtime_HOME + "/voxels"))));

        return path(XDG_Runtime_HOME + "/voxels/");
    }

    // base XDG specified directories
    result<path> Get(const variables_map &VariableMap) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        static result<path> RuntimeHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

        if (RuntimeHomeResult) {
            return RuntimeHomeResult.value();
        }

        RuntimeHomeResult = GetPathFromProgramOptions(VariableMap, RuntimeHomeFlag);

        if (RuntimeHomeResult) {
            path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found Runtime home: '" << RuntimeHome.string() <<  "' from program options flag: '" << RuntimeHomeFlag << "'";
            #endif

            return RuntimeHome;
        }

         #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine config home from program options flag: '" << RuntimeHomeFlag << "'";
        #endif


        RuntimeHomeResult = GetRuntimeHomeFromVoxels();

        if (RuntimeHomeResult) {
            path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from environment variable: 'VOXELS_RUNTIME_HOME'";
            #endif

            return RuntimeHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine runtime home from environment variable: 'VOXELS_RUNTIME_HOME'";
        #endif


        RuntimeHomeResult = GetRuntimeHomeFromXDG();

        if (RuntimeHomeResult) {
            path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                 BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from environment variable: 'XDG_RUNTIME_DIR'";
            #endif

            return RuntimeHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine runtime home from environment variable: 'XDG_RUNTIME_DIR'";
        #endif

        return BOOST_LEAF_NEW_ERROR(NoCandidate);
    }



}
