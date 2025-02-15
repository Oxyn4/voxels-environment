#include "voxels/directories/voxels/Logs.hpp"

#include "../ProgramOptions.hpp"

namespace Directories::Voxels::Logs
{

    std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &StateHome) noexcept {
        boost::leaf::result<std::filesystem::path> LogsHomeResult = GetPathFromProgramOptions(VariableMap, LogsHomeFlag);

        if (LogsHomeResult) {
            std::filesystem::path LogsHome = LogsHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found Logs home: '" << LogsHome.string() <<  "' from program option: '" << LogsHomeFlag <<  "'";

            return LogsHome;
        }
    
        BOOST_LOG_TRIVIAL(warning) << "Could not determine Logs home from program options flag: '" << LogsHomeFlag << "'";

        std::filesystem::path StateHomeCopy = StateHome;

        StateHomeCopy.append("logs/");

        BOOST_LOG_TRIVIAL(trace) << "Found Logs Home: '" << StateHomeCopy.string() << "'";

        return StateHomeCopy;
    }





}
