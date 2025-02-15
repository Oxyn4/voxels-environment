// public interface
#include "voxels/directories/base/Runtime.hpp"

#include "../EnviromentVariables.hpp"
#include "../ProgramOptions.hpp"

#include <boost/leaf/error.hpp>

#include "Logging.hpp"

namespace voxels::directories::base::runtime
{

    boost::leaf::result<void> Validate(const std::filesystem::path& RuntimeHome) noexcept {
        if (not std::filesystem::exists(RuntimeHome)) {
            return boost::leaf::new_error(DoesNotExist);
        }

        if (not std::filesystem::is_directory(RuntimeHome)) {
            return boost::leaf::new_error(NotDirectoryError);
        }

        return {};
    }

    boost::leaf::result<std::filesystem::path> GetRuntimeHomeFromVoxels() noexcept {
        BOOST_LEAF_AUTO(const VOXELS_Runtime_HOME, GetEnvironmentVariable("VOXELS_RUNTIME_HOME"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((VOXELS_Runtime_HOME))));

        return std::filesystem::path(VOXELS_Runtime_HOME);
    }

    boost::leaf::result<std::filesystem::path> GetRuntimeHomeFromXDG() noexcept {
        BOOST_LEAF_AUTO(const XDG_Runtime_HOME, GetEnvironmentVariable("XDG_RUNTIME_DIR"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((XDG_Runtime_HOME + "/voxels"))));

        return std::filesystem::path(XDG_Runtime_HOME + "/voxels/");
    }

    // base XDG specified directories
    boost::leaf::result<std::filesystem::path> GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept {
        #ifndef NO_LOG
            auto DirectoriesLogger = DirectoriesLoggerTag::get();
        #endif

        static boost::leaf::result<std::filesystem::path> RuntimeHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

        if (RuntimeHomeResult) {
            return RuntimeHomeResult.value();
        }

        RuntimeHomeResult = GetPathFromProgramOptions(VariableMap, RuntimeHomeFlag);

        if (RuntimeHomeResult) {
            std::filesystem::path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Runtime home: '" << RuntimeHome.string() <<  "' from program options flag: '" << RuntimeHomeFlag << "'";
            #endif

            return RuntimeHome;
        }

         #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine config home from program options flag: '" << RuntimeHomeFlag << "'";
        #endif


        RuntimeHomeResult = GetRuntimeHomeFromVoxels();

        if (RuntimeHomeResult) {
            std::filesystem::path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from environment variable: 'VOXELS_RUNTIME_HOME'";
            #endif

            return RuntimeHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine runtime home from environment variable: 'VOXELS_RUNTIME_HOME'";
        #endif


        RuntimeHomeResult = GetRuntimeHomeFromXDG();

        if (RuntimeHomeResult) {
            std::filesystem::path RuntimeHome = RuntimeHomeResult.value();

            #ifndef NO_LOG
                 BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from environment variable: 'XDG_RUNTIME_DIR'";
            #endif

            return RuntimeHome;
        }

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine runtime home from environment variable: 'XDG_RUNTIME_DIR'";
        #endif

        return BOOST_LEAF_NEW_ERROR(NoCandidate);
    }



}
