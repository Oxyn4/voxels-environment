#include <voxels/directories/Directories.hpp>

#include <iostream>

int main(const int ac, char** av)
{
    boost::program_options::options_description OptionsDescription("Voxels example: mods directory");

    voxels::directories::AddProgramOptions(OptionsDescription);

    boost::program_options::variables_map VariableMap;

    store(parse_command_line(ac, av, OptionsDescription), VariableMap);

    boost::leaf::result<std::filesystem::path> DataHomeResult = voxels::directories::base::data::GetCandidates(VariableMap);

    boost::leaf::result<std::filesystem::path> ModsHomeResult = voxels::directories::voxels::mods::Get(VariableMap, DataHomeResult.value());

    std::cout << ModsHomeResult.value() << std::endl;
}