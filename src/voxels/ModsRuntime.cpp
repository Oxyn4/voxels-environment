
#include "voxels/directories/voxels/ModsRuntime.hpp"

#include "../ProgramOptions.hpp"

#include "Logging.hpp"

namespace voxels::directories::voxels::mods_runtime {

std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &RuntimeHome) noexcept {
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    boost::leaf::result<std::filesystem::path> ModsRuntimeHomeResult = GetPathFromProgramOptions(VariableMap, ModsRuntimeFlag);

    if (ModsRuntimeHomeResult) {
        std::filesystem::path ModsRuntimeHome = ModsRuntimeHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found ModsRuntime home: '" << ModsRuntimeHome.string() <<  "' from program option: '" << ModsRuntimeFlag <<  "'";
        #endif

        return ModsRuntimeHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine ModsRuntime home from program options flag: '" << ModsRuntimeFlag << "'";
    #endif

    std::filesystem::path RuntimeHomeCopy = RuntimeHome;

    RuntimeHomeCopy.append("mods/");

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods Runtime Home: '" << RuntimeHomeCopy.string() << "'";
    #endif

    return RuntimeHomeCopy;
} 



}
