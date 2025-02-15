#include <voxels/directories/voxels/certs.hpp>

#include <boost/leaf.hpp>

#include "../ProgramOptions.hpp"

#include "logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::voxels::certs
{
    path Get(const variables_map &VariableMap, const path &DataHome) noexcept {
        #ifndef NO_LOG
                auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        if (result<path> LogsHomeResult = GetPathFromProgramOptions(VariableMap, AccountsHomeFlag)) {
            path LogsHome = LogsHomeResult  .value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found certs home: '" << LogsHome.string() <<  "' from program option: '" << AccountsHomeFlag <<  "'";
        #endif

            return LogsHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine certs home from program options flag: '" << AccountsHomeFlag << "'";
        #endif

        path DataHomeCopy = DataHome;

        DataHomeCopy.append("certs/");

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found certs Home: '" << DataHomeCopy.string() << "'";
        #endif

        return DataHomeCopy;
    }

    path GetSignature(const path &CertsHome) noexcept {
        #ifndef NO_LOG
                auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        path CertsHomeCopy = CertsHome;

        CertsHomeCopy.append("signatures/");

        #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found signature Home: '" << CertsHomeCopy.string() << "'";
        #endif

        return CertsHomeCopy;
    }

    path GetPrivate(const path &CertsHome) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        path CertsHomeCopy = CertsHome;

        CertsHomeCopy.append("private/");

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found private Home: '" << CertsHomeCopy.string() << "'";
        #endif

        return CertsHomeCopy;
    }
}