#include <voxels/directories/Directories.hpp>

#include <iostream>

int main(const int ac, char** av)
{
    boost::program_options::options_description OptionsDescription("Voxels example: logs directory");

    voxels::directories::AddProgramOptions(OptionsDescription);

    boost::program_options::variables_map VariableMap;

    store(parse_command_line(ac, av, OptionsDescription), VariableMap);

    boost::leaf::result<std::filesystem::path> StateHomeResult = voxels::directories::base::state::GetCandidates(VariableMap);

    boost::leaf::result<std::filesystem::path> LogsHomeResult = voxels::directories::voxels::logs::Get(VariableMap, StateHomeResult.value());

    std::cout << LogsHomeResult.value() << std::endl;
}