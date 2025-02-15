
#include "voxels/directories/voxels/ModsLogs.hpp"

#include "../ProgramOptions.hpp"

#include "Logging.hpp"

namespace voxels::directories::voxels::mods_logs
{

    std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &StateHome) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        boost::leaf::result<std::filesystem::path> ModsLogsRuntimeHomeResult = GetPathFromProgramOptions(VariableMap, ModsLogsHomeFlag);

        if (ModsLogsRuntimeHomeResult) {
            std::filesystem::path ModsLogsHome = ModsLogsRuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found ModsLogs home: '" << ModsLogsHome.string() <<  "' from program option: '" << ModsLogsHomeFlag <<  "'";
            #endif

            return ModsLogsHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine ModsLogs home from program options flag: '" << ModsLogsHomeFlag << "'";
        #endif

        std::filesystem::path StateHomeCopy = StateHome;
    
        StateHomeCopy.append("mods/logs");

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods Logs Home: '" << StateHomeCopy.string() << "'";
        #endif

        return StateHomeCopy;
    }



}
