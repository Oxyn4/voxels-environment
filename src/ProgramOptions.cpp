
// public definitions
#include "voxels/directories/ProgramOptions.hpp"

#include "voxels/directories/voxels/voxels.hpp"
#include "voxels/directories/base/base.hpp"

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

namespace voxels::directories {
    void AddProgramOptions(boost::program_options::options_description &OptionsDescription) noexcept {
        OptionsDescription.add_options()
            (base::config::ConfigHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the configuration folder, equivalent to environment variable: VOXELS_CONFIG_HOME but is higher in priority")
            (base::state::StateHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the state folder, equivalent to environment variable: VOXELS_STATE_HOME but is higher in priority")
            (base::runtime::RuntimeHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the runtime folder, equivalent to environment variable: VOXELS_RUNTIME_HOME but is higher in priority")
            (base::data::DataHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the data folder, equivalent to environment variable: VOXELS_DATA_HOME but is higher in priority")
            (voxels::mods::ModsHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the mods folder, equivalent to environment variable: VOXELS_MODS_HOME but is higher in priority")
            (voxels::mods_runtime::ModsRuntimeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the mods runtime folder, equivalent to environment variable: VOXELS_RUNTIME_HOME but is higher in priority")
            (voxels::mods_logs::ModsLogsHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the mods logging folder, equivalent to environment variable: VOXELS_MODS_LOGS_HOME but is higher in priority")
            (voxels::logs::LogsHomeFlag.c_str(), boost::program_options::value<std::filesystem::path>(), "Sets the root directory of the logging folder, equivalent to environment variable: VOXELS_LOGS_HOME but is higher in priority");
    }
}


