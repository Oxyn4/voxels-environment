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
