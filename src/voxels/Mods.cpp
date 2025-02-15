
#include "voxels/directories/voxels/Mods.hpp"

#include "../ProgramOptions.hpp"

#include "Logging.hpp"

namespace voxels::directories::voxels::mods {

std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &DataHome) noexcept {
    #ifndef NO_LOG
        auto DirectoriesLogger = DirectoriesLoggerTag::get();
    #endif

    boost::leaf::result<std::filesystem::path> ModsHomeResult = GetPathFromProgramOptions(VariableMap, ModsHomeFlag);

    if (ModsHomeResult) {
        std::filesystem::path ModsHome = ModsHomeResult.value();

        #ifndef NO_LOG
            BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods home: '" << ModsHome.string() <<  "' from program option: '" << ModsHomeFlag <<  "'";
        #endif

        return ModsHome;
    }

    #ifndef NO_LOG
        BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::warning) << "Could not determine Mods home from program options flag: '" << ModsHomeFlag << "'";
    #endif

    std::filesystem::path DataHomeCopy = DataHome;

    DataHomeCopy.append("mods/");

    #ifndef NO_LOG
         BOOST_LOG_SEV(DirectoriesLogger,  boost::log::trivial::trace) << "Found Mods Home: '" << DataHomeCopy.string() << "'";
    #endif

    return DataHomeCopy;
}



}
