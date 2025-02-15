
#include "voxels/directories/voxels/ModsLogs.hpp"

#include "../ProgramOptions.hpp"

#include "Logging.hpp"

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
