project(
    Directories
    VERSION 0.1.0
    DESCRIPTION "Base directories is a utility library to find common directories needed for execution"
    HOMEPAGE_URL "https://www.github.com/Oxyn4/voxels-directories"
    LANGUAGES CXX
)

find_package(Boost CONFIG REQUIRED COMPONENTS log program_options)

set(directories_files
        src/EnvironmentVariables.cpp
        src/ProgramOptions.cpp
)

if (NOT NO_BASE_CONFIG)
    message(STATUS "adding support for voxels::directories::base::config")
    list(APPEND directories_files
            src/base/Config.cpp
    )
endif()

if (NOT DEFINED NO_BASE_DATA)
    message(STATUS "adding support for voxels::directories::base::data")
    list(APPEND directories_files
            src/base/Data.cpp
    )
endif()

if (NOT DEFINED NO_BASE_RUNTIME)
    message(STATUS "adding support for voxels::directories::base::data")
    list(APPEND directories_files
            src/base/Runtime.cpp
    )
endif()

if (NOT DEFINED NO_BASE_CONFIG)
    message(STATUS "adding support for voxels::directories::base::config")
    list(APPEND directories_files
            src/base/State.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_LOGS)
    message(STATUS "adding support for voxels::directories::voxels::logs")
    list(APPEND directories_files
            src/voxels/Logs.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_MODS)
    message(STATUS "adding support for voxels::directories::voxels::mods")
    list(APPEND directories_files
            src/voxels/Mods.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_MODS_RUNTIME)
    message(STATUS "adding support for voxels::directories::voxels::mods_runtime")
    list(APPEND directories_files
            src/voxels/ModsRuntime.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_MODS_LOGS)
    message(STATUS "adding support for voxels::directories::voxels::mods_logs")
    list(APPEND directories_files
            src/voxels/ModsLogs.cpp
    )
endif()

add_library(directories STATIC
    ${directories_files}
)

target_include_directories(directories PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NOT DEFINED NO_LOG)
    target_link_libraries(directories Boost::log)
endif()

target_link_libraries(directories Boost::program_options)

if (DEFINED BUILD_EXAMPLES)
    message(STATUS "Building examples for voxels directories")

    add_executable(directories_examples_base_config
        examples/base/config.cpp
    )

    target_link_libraries(directories_examples_base_config directories)

    add_executable(directories_examples_base_state
            examples/base/state.cpp
    )

    target_link_libraries(directories_examples_base_state directories)

    add_executable(directories_examples_base_data
            examples/base/data.cpp
    )

    target_link_libraries(directories_examples_base_data directories)

    add_executable(directories_examples_base_runtime
            examples/base/runtime.cpp
    )

    target_link_libraries(directories_examples_base_runtime directories)

    add_executable(directories_examples_voxels_logs
            examples/voxels/logs.cpp
    )

    target_link_libraries(directories_examples_voxels_logs directories)

    add_executable(directories_examples_voxels_mods
            examples/voxels/mods.cpp
    )

    target_link_libraries(directories_examples_voxels_mods directories)

    add_executable(directories_examples_voxels_mods_logs
            examples/voxels/mods_logs.cpp
    )

    target_link_libraries(directories_examples_voxels_mods_logs directories)

    add_executable(directories_examples_voxels_mods_runtime
            examples/voxels/mods_runtime.cpp
    )

    target_link_libraries(directories_examples_voxels_mods_runtime directories)
endif ()
