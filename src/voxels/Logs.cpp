#include "voxels/directories/voxels/Logs.hpp"

#include "../ProgramOptions.hpp"

#include "Logging.hpp"

namespace voxels::directories::voxels::logs
{

    std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &StateHome) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

            if (boost::leaf::result<std::filesystem::path> LogsHomeResult = GetPathFromProgramOptions(VariableMap, LogsHomeFlag)) {
            std::filesystem::path LogsHome = LogsHomeResult.value();

            #ifndef NO_LOG
                 BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Logs home: '" << LogsHome.string() <<  "' from program option: '" << LogsHomeFlag <<  "'";
            #endif

            return LogsHome;
        }

        #ifndef NO_LOG
             BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine Logs home from program options flag: '" << LogsHomeFlag << "'";
        #endif

        std::filesystem::path StateHomeCopy = StateHome;

        StateHomeCopy.append("logs/");

        #ifndef NO_LOG
             BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Logs Home: '" << StateHomeCopy.string() << "'";
        #endif

        return StateHomeCopy;
    }





}
