
// public definitions
#include "voxel-directories/base/base.hpp"
#include "voxel-directories/voxels/voxels.hpp"

// private definitions
#include "ProgramOptions.hpp"

boost::leaf::result<std::filesystem::path> GetPathFromProgramOptions(const boost::program_options::variables_map& VariableMap, const std::string& Flag) noexcept {
    if (VariableMap.count(Flag) != 1) {return BOOST_LEAF_NEW_ERROR(NotPresent);}

    return boost::leaf::exception_to_result<boost::program_options::error, boost::program_options::error_with_option_name, boost::program_options::error_with_no_option_name>(
        [&VariableMap, &Flag](){
            return VariableMap[Flag].as<std::filesystem::path>();
        }
    );
}

namespace Directories {
    void AddBaseDirectoriesProgramOptions(boost::program_options::options_description &OptionsDescription) noexcept {
        OptionsDescription.add_options()
            (Base::Config::ConfigHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the configuration folder, equivelent to enviroment variable: VOXELS_CONFIG_HOME but is higher in priority")
            (Base::State::StateHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the state folder, equivelent to enviroment variable: VOXELS_STATE_HOME but is higher in priority")
            (Base::Runtime::RuntimeHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the runtime folder, equivelent to enviroment variable: VOXELS_RUNTIME_HOME but is higher in priority")
            (Base::Data::DataHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the data folder, equivelent to enviroment variable: VOXELS_DATA_HOME but is higher in priority")
            (Voxels::Mods::ModsHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the mods folder, equivelent to enviroment variable: VOXELS_MODS_HOME but is higher in priority")
            (Voxels::ModsRuntime::ModsRuntimeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the mods runtime folder, equivelent to enviroment variable: VOXELS_RUNTIME_HOME but is higher in priority")
            (Voxels::ModsLogs::ModsLogsHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the mods logging folder, equivelent to enviroment variable: VOXELS_MODS_LOGS_HOME but is higher in priority")
            (Voxels::Logs::LogsHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the logging folder, equivelent to enviroment variable: VOXELS_LOGS_HOME but is higher in priority");
    }
}


