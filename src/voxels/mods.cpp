// This file is part of the voxels environment library.
// the voxels environment library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// the voxels environment library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with the voxels environment library. If not,
// see <https://www.gnu.org/licenses/>.

#include "voxels/directories/voxels/Mods.hpp"

#include "../ProgramOptions.hpp"

#include "logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::voxels::mods {

path Get(const variables_map &VariableMap, const path &DataHome) noexcept {
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    if (result<path> ModsHomeResult = GetPathFromProgramOptions(VariableMap, ModsHomeFlag)) {
        path ModsHome = ModsHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods home: '" << ModsHome.string() <<  "' from program option: '" << ModsHomeFlag <<  "'";
        #endif

        return ModsHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine Mods home from program options flag: '" << ModsHomeFlag << "'";
    #endif

    path DataHomeCopy = DataHome;

    DataHomeCopy.append("mods/");

    #ifndef NO_LOG
         BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods Home: '" << DataHomeCopy.string() << "'";
    #endif

    return DataHomeCopy;
}



}
