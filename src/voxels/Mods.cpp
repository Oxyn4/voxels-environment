
#include "voxels/directories/voxels/Mods.hpp"

#include "../ProgramOptions.hpp"



namespace voxels::directories::voxels::mods {

std::filesystem::path Get(const boost::program_options::variables_map &VariableMap, const std::filesystem::path &DataHome) noexcept {
    boost::leaf::result<std::filesystem::path> ModsHomeResult = GetPathFromProgramOptions(VariableMap, ModsHomeFlag);

    if (ModsHomeResult) {
        std::filesystem::path ModsHome = ModsHomeResult.value();

        BOOST_LOG_TRIVIAL(trace) << "Found Mods home: '" << ModsHome.string() <<  "' from program option: '" << ModsHomeFlag <<  "'";

        return ModsHome;
    }
    
    BOOST_LOG_TRIVIAL(warning) << "Could not determine Mods home from program options flag: '" << ModsHomeFlag << "'";

    std::filesystem::path DataHomeCopy = DataHome;

    DataHomeCopy.append("mods/");
    
    BOOST_LOG_TRIVIAL(trace) << "Found Mods Home: '" << DataHomeCopy.string() << "'";

    return DataHomeCopy;
}



}
