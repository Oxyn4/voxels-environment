project(
    BaseDirectories
    VERSION 0.1.0
    DESCRIPTION "Base directories is a utility library to find common directories needed for execution"
    HOMEPAGE_URL "https://www.github.com/Oxyn4/Voxels-base-directories"
    LANGUAGES CXX
)

add_library(BaseDirectories STATIC 
    src/base/Config.cpp
    src/base/Data.cpp
    src/base/Runtime.cpp
    src/base/State.cpp
    src/voxels/Logs.cpp
    src/voxels/Mods.cpp
    src/voxels/ModsRuntime.cpp
    src/voxels/ModsLogs.cpp
    src/EnviromentVariables.cpp
    src/ProgramOptions.cpp
)

target_include_directories(BaseDirectories PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(BaseDirectories Boost::log Boost::log_setup Boost::program_options)
