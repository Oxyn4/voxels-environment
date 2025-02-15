
#include "voxels/directories/voxels/ModsRuntime.hpp"

#include "../ProgramOptions.hpp"

namespace Directories {
    namespace Voxels {
        namespace ModsRuntime {

std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &RuntimeHome) noexcept {
    boost::leaf::result<std::filesystem::path> ModsRuntimeHomeResult = GetPathFromProgramOptions(VariableMap, ModsRuntimeFlag);

    if (ModsRuntimeHomeResult) {
        std::filesystem::path ModsRuntimeHome = ModsRuntimeHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found ModsRuntime home: '" << ModsRuntimeHome.string() <<  "' from program option: '" << ModsRuntimeFlag <<  "'";

        return ModsRuntimeHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine ModsRuntime home from program options flag: '" << ModsRuntimeFlag << "'";

    std::filesystem::path RuntimeHomeCopy = RuntimeHome;

    RuntimeHomeCopy.append("mods/");
   
    BOOST_LOG_TRIVIAL(trace) << "Found Mods Runtime Home: '" << RuntimeHomeCopy.string() << "'";

    return RuntimeHomeCopy;
} 



}}}
