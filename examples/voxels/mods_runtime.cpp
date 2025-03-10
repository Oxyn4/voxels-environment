#include <voxels/directories/Directories.hpp>

#include <iostream>

int main(const int ac, char** av)
{
    boost::program_options::options_description OptionsDescription("Voxels example: mods runtime library");

    voxels::directories::AddProgramOptions(OptionsDescription);

    boost::program_options::variables_map VariableMap;

    store(parse_command_line(ac, av, OptionsDescription), VariableMap);

    boost::leaf::result<std::filesystem::path> RuntimeHomeResult = voxels::directories::base::runtime::Get(VariableMap);

    boost::leaf::result<std::filesystem::path> ModsRuntimeHomeResult = voxels::directories::voxels::mods_runtime::Get(VariableMap, RuntimeHomeResult.value());

    std::cout << ModsRuntimeHomeResult.value() << std::endl;
}