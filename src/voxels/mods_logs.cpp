// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

#include "voxels/directories/voxels/ModsLogs.hpp"

#include "../ProgramOptions.hpp"

#include "logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::voxels::mods_logs
{

    path Get(const variables_map &VariableMap, const path &StateHome) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        result<path> ModsLogsRuntimeHomeResult = GetPathFromProgramOptions(VariableMap, ModsLogsHomeFlag);

        if (ModsLogsRuntimeHomeResult) {
            path ModsLogsHome = ModsLogsRuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found ModsLogs home: '" << ModsLogsHome.string() <<  "' from program option: '" << ModsLogsHomeFlag <<  "'";
            #endif

            return ModsLogsHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine ModsLogs home from program options flag: '" << ModsLogsHomeFlag << "'";
        #endif

        path StateHomeCopy = StateHome;
    
        StateHomeCopy.append("mods/logs");

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods Logs Home: '" << StateHomeCopy.string() << "'";
        #endif

        return StateHomeCopy;
    }



}
