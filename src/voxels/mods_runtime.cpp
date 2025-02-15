// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

#include "voxels/directories/voxels/ModsRuntime.hpp"

#include "../ProgramOptions.hpp"

#include "logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::voxels::mods_runtime {

path Get(const variables_map &VariableMap, const path &RuntimeHome) noexcept {
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    result<path> ModsRuntimeHomeResult = GetPathFromProgramOptions(VariableMap, ModsRuntimeFlag);

    if (ModsRuntimeHomeResult) {
        path ModsRuntimeHome = ModsRuntimeHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found ModsRuntime home: '" << ModsRuntimeHome.string() <<  "' from program option: '" << ModsRuntimeFlag <<  "'";
        #endif

        return ModsRuntimeHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine ModsRuntime home from program options flag: '" << ModsRuntimeFlag << "'";
    #endif

    path RuntimeHomeCopy = RuntimeHome;

    RuntimeHomeCopy.append("mods/");

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods Runtime Home: '" << RuntimeHomeCopy.string() << "'";
    #endif

    return RuntimeHomeCopy;
} 



}
