

// public interface
#include "voxels/directories/base/Runtime.hpp"

#include "../EnvironmentVariables.hpp"
#include "../ProgramOptions.hpp"

#include <boost/leaf/error.hpp>

#include "Logging.hpp"

using namespace boost::leaf;

using namespace std::filesystem;

using namespace boost::log::trivial;

using namespace boost::program_options;

namespace voxels::directories::base::runtime
{

    result<void> Validate(const path& RuntimeHome) noexcept {
        if (not exists(RuntimeHome)) {
            return new_error(DoesNotExist);
        }

        if (not is_directory(RuntimeHome)) {
            return new_error(NotDirectoryError);
        }

        return {};
    }

    result<path> GetRuntimeHomeFromVoxels() noexcept {
        BOOST_LEAF_AUTO(const VOXELS_Runtime_HOME, GetEnvironmentVariable("VOXELS_RUNTIME_HOME"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((VOXELS_Runtime_HOME))));

        return path(VOXELS_Runtime_HOME);
    }

    result<path> GetRuntimeHomeFromXDG() noexcept {
        BOOST_LEAF_AUTO(const XDG_Runtime_HOME, GetEnvironmentVariable("XDG_RUNTIME_DIR"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((XDG_Runtime_HOME + "/voxels"))));

        return path(XDG_Runtime_HOME + "/voxels/");
    }

    // base XDG specified directories
    result<path> GetCandidates(const variables_map &VariableMap) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        static result<path> RuntimeHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

        if (RuntimeHomeResult) {
            return RuntimeHomeResult.value();
        }

        RuntimeHomeResult = GetPathFromProgramOptions(VariableMap, RuntimeHomeFlag);

        if (RuntimeHomeResult) {
            path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found Runtime home: '" << RuntimeHome.string() <<  "' from program options flag: '" << RuntimeHomeFlag << "'";
            #endif

            return RuntimeHome;
        }

         #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine config home from program options flag: '" << RuntimeHomeFlag << "'";
        #endif


        RuntimeHomeResult = GetRuntimeHomeFromVoxels();

        if (RuntimeHomeResult) {
            path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from environment variable: 'VOXELS_RUNTIME_HOME'";
            #endif

            return RuntimeHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine runtime home from environment variable: 'VOXELS_RUNTIME_HOME'";
        #endif


        RuntimeHomeResult = GetRuntimeHomeFromXDG();

        if (RuntimeHomeResult) {
            path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                 BOOST_LOG_SEV(DirectoriesLogger,  trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from environment variable: 'XDG_RUNTIME_DIR'";
            #endif

            return RuntimeHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  warning) << "Could not determine runtime home from environment variable: 'XDG_RUNTIME_DIR'";
        #endif

        return BOOST_LEAF_NEW_ERROR(NoCandidate);
    }



}
