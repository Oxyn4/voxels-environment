
#include "voxels/directories/voxels/ModsLogs.hpp"

#include "../ProgramOptions.hpp"

namespace voxels::directories::voxels::mods_logs
{

    std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &StateHome) noexcept {
        boost::leaf::result<std::filesystem::path> ModsLogsRuntimeHomeResult = GetPathFromProgramOptions(VariableMap, ModsLogsHomeFlag);

        if (ModsLogsRuntimeHomeResult) {
            std::filesystem::path ModsLogsHome = ModsLogsRuntimeHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found ModsLogs home: '" << ModsLogsHome.string() <<  "' from program option: '" << ModsLogsHomeFlag <<  "'";

            return ModsLogsHome;
        }
    
        BOOST_LOG_TRIVIAL(warning) << "Could not determine ModsLogs home from program options flag: '" << ModsLogsHomeFlag << "'";

        std::filesystem::path StateHomeCopy = StateHome;
    
        StateHomeCopy.append("mods/logs");
    
        BOOST_LOG_TRIVIAL(trace) << "Found Mods Logs Home: '" << StateHomeCopy.string() << "'";

        return StateHomeCopy;
    }



}
