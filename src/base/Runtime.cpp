// public interface
#include "voxels/directories/base/Runtime.hpp"


#include "../EnviromentVariables.hpp"

#include "../ProgramOptions.hpp"

#include <boost/leaf/error.hpp>

namespace Directories::Base::Runtime
{

    boost::leaf::result<void> Validate(std::filesystem::path RuntimeHome) noexcept {
        if (!std::filesystem::exists(RuntimeHome)) {
            return boost::leaf::new_error(DoesNotExist);
        }

        if (std::filesystem::is_directory(RuntimeHome)) {
            return boost::leaf::new_error(NotDirectoryError);
        }

        return {};
    }

    boost::leaf::result<std::filesystem::path> GetRuntimeHomeFromVoxels() noexcept {
        BOOST_LEAF_AUTO(VOXELS_Runtime_HOME, GetEnvironmentVariable("VOXELS_RUNTIME_HOME"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((VOXELS_Runtime_HOME))));

        return std::filesystem::path(VOXELS_Runtime_HOME);
    }

    boost::leaf::result<std::filesystem::path> GetRuntimeHomeFromXDG() noexcept {
        BOOST_LEAF_AUTO(XDG_Runtime_HOME, GetEnvironmentVariable("XDG_RUNTIME_DIR"));

        BOOST_LEAF_CHECK(Validate(std::filesystem::path((XDG_Runtime_HOME + "/voxels"))));

        return std::filesystem::path(XDG_Runtime_HOME + "/voxels/");
    }

    // base XDG specified directories
    boost::leaf::result<std::filesystem::path> GetCandidates(const boost::program_options::variables_map &VariableMap) noexcept {
        static boost::leaf::result<std::filesystem::path> RuntimeHomeResult = BOOST_LEAF_NEW_ERROR(NotSet);

        if (RuntimeHomeResult) {
            return RuntimeHomeResult.value();
        }

        RuntimeHomeResult = GetPathFromProgramOptions(VariableMap, RuntimeHomeFlag);

        if (RuntimeHomeResult) {
            std::filesystem::path RuntimeHome = RuntimeHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found Runtime home: '" << RuntimeHome.string() <<  "' from program options flag: '" << RuntimeHomeFlag << "'";

            return RuntimeHome;
        }

        BOOST_LOG_TRIVIAL(warning) << "Could not determine config home from program options flag: '" << RuntimeHomeFlag << "'";

        RuntimeHomeResult = GetRuntimeHomeFromVoxels();

        if (RuntimeHomeResult) {
            std::filesystem::path RuntimeHome = RuntimeHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from enviroment variable: 'VOXELS_RUNTIME_HOME'";

            return RuntimeHome;
        }

        BOOST_LOG_TRIVIAL(warning) << "Could not determine runtime home from enviroment variable: 'VOXELS_RUNTIME_HOME'";

        RuntimeHomeResult = GetRuntimeHomeFromXDG();

        if (RuntimeHomeResult) {
            std::filesystem::path RuntimeHome = RuntimeHomeResult.value();

            BOOST_LOG_TRIVIAL(trace) << "Found runtime home: '" << RuntimeHome.string() <<  "' from enviroment variable: 'XDG_RUNTIME_DIR'";

            return RuntimeHome;
        }

        BOOST_LOG_TRIVIAL(warning) << "Could not determine runtime home from enviroment variable: 'XDG_RUNTIME_DIR'";

        return BOOST_LEAF_NEW_ERROR(NoCandidate);
    }



}
