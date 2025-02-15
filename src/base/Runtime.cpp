#include "voxel-directories/base/Runtime.hpp"

#include "../EnviromentVariables.hpp"

#include "../ProgramOptions.hpp"

namespace Directories {
    namespace Base {
        namespace Runtime {

boost::leaf::result<void> Validate(std::filesystem::path& RuntimeHome) noexcept {}

boost::leaf::result<std::filesystem::path> GetRuntimeHomeFromVoxels() noexcept {
    BOOST_LEAF_AUTO(VOXELS_Runtime_HOME, GetEnviromentVariable("VOXELS_RUNTIME_HOME"));

    return std::filesystem::path(VOXELS_Runtime_HOME);
}

boost::leaf::result<std::filesystem::path> GetRuntimeHomeFromXDG() noexcept {
    BOOST_LEAF_AUTO(XDG_Runtime_HOME, GetEnviromentVariable("XDG_RUNTIME_DIR"));

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
    }
}
