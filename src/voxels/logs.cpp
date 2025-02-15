// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

#include "voxels/directories/voxels/Logs.hpp"

#include "../ProgramOptions.hpp"

#include "logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::voxels::logs
{

    path Get(const variables_map &VariableMap, const path &DataHome) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

            if (result<path> LogsHomeResult = GetPathFromProgramOptions(VariableMap, AccountsHomeFlag)) {
            path LogsHome = LogsHomeResult.value();

            #ifndef NO_LOG
                 BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Logs home: '" << LogsHome.string() <<  "' from program option: '" << AccountsHomeFlag <<  "'";
            #endif

            return LogsHome;
        }

        #ifndef NO_LOG
             BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine Logs home from program options flag: '" << AccountsHomeFlag << "'";
        #endif

        path StateHomeCopy = DataHome;

        StateHomeCopy.append("logs/");

        #ifndef NO_LOG
             BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Logs Home: '" << StateHomeCopy.string() << "'";
        #endif

        return StateHomeCopy;
    }





}
