
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
