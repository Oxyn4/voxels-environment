cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
)

find_package(Doxygen)

if (DOXYGEN_FOUND)
    message(STATUS "Found doxygen")
    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else()
    message(STATUS "Unable to find Doxygen")
endif ()

if (NOT DEFINED NO_PROGRAM_OPTIONS)
    message(STATUS "adding support for voxels::directories::program_options")
    list(APPEND directories_files
            src/ProgramOptions.cpp
    )
endif()

if (NOT DEFINED NO_BASE_CONFIG)
    message(STATUS "adding support for voxels::directories::base::config")
    list(APPEND directories_files
            src/base/data.cpp
    )
endif()

if (NOT DEFINED NO_BASE_DATA)
    message(STATUS "adding support for voxels::directories::base::data")
    list(APPEND directories_files
            src/base/data.cpp
    )
endif()

if (NOT DEFINED NO_BASE_RUNTIME)
    message(STATUS "adding support for voxels::directories::base::data")
    list(APPEND directories_files
            src/base/runtime.cpp
    )
endif()

if (NOT DEFINED NO_BASE_CONFIG)
    message(STATUS "adding support for voxels::directories::base::config")
    list(APPEND directories_files
            src/base/config.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_LOGS)
    message(STATUS "adding support for voxels::directories::voxels::logs")
    list(APPEND directories_files
            src/voxels/logs.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_MODS)
    message(STATUS "adding support for voxels::directories::voxels::mods")
    list(APPEND directories_files
            src/voxels/mods.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_MODS_RUNTIME)
    message(STATUS "adding support for voxels::directories::voxels::mods_runtime")
    list(APPEND directories_files
            src/voxels/mods_runtime.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_MODS_LOGS)
    message(STATUS "adding support for voxels::directories::voxels::mods_logs")
    list(APPEND directories_files
            src/voxels/mods_logs.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_CERTS)
    message(STATUS "adding support for voxels::directories::voxels::certs")
    list(APPEND directories_files
            src/voxels/certs.cpp
    )
endif()

if (NOT DEFINED NO_VOXELS_ACCOUNTS)
    message(STATUS "adding support for voxels::directories::voxels::accounts")
    list(APPEND directories_files
            src/voxels/accounts.cpp
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

if (NOT DEFINED NO_PROGRAM_OPTIONS)
    target_link_libraries(directories Boost::program_options)
endif ()

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
