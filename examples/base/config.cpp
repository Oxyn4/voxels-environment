#include <voxels/directories/ProgramOptions.hpp>
#include <voxels/directories/base/Config.hpp>

using namespace voxels::directories;

int main(const int ac, char** av)
{
    boost::program_options::options_description OptionsDescription("Voxels example: xdg base config");

    voxels::directories::AddProgramOptions(OptionsDescription);

    boost::program_options::variables_map VariableMap;

    store(parse_command_line(ac, av, OptionsDescription), VariableMap);

    boost::leaf::result<std::filesystem::path> ConfigHomeResult = base::config::Get(VariableMap);
}
