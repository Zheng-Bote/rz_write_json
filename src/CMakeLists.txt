cmake_minimum_required(VERSION 3.23)

# To build the project, run the following commands in the terminal: cmake
# --build . --target 'clean' cmake -S ../src -B . -DCMAKE_BUILD_TYPE=Release
# cmake --build . --parallel 6 --config Release

# flatc --cpp rz_write_flatbuffers.fbs -- output to includes/ flatc --json
# [--raw-binary] rz_write_flatbuffers.fbs -- rz_write_flatbuffers.bin flatc
# --jsonschema rz_write_flatbuffers.fbs

project(
  rz_write_json
  VERSION 0.2.1
  DESCRIPTION
    "Plugin to export Metadata to BSON, CBOR, MessagePack, UBJSON, and BJData formats"
  HOMEPAGE_URL "https://github.com/Zheng-Bote/rz_write_json"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_NAME "${PROJECT_NAME}")
set(PROG_LONGNAME "write Binary formats")
set(PROG_CREATED "2025")
set(PROG_AUTHOR "ZHENG Bote")
set(PROG_ORGANIZATION_NAME "ZHENG Robert")
set(PROG_ORGANIZATION_DOMAIN "net.hase-zheng")
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
set(CMAKE_QTV "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")

# if(CMAKE_SYSTEM_NAME STREQUAL "Linux") set(CMAKE_CXX_COMPILER clang++) endif()

add_subdirectory(configure)

include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3)

FetchContent_MakeAvailable(nlohmann_json)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

# add_executable(${PROJECT_NAME} main.cpp)
add_library(
  ${PROJECT_NAME} SHARED
  rz_write_json.cpp includes/rz_write_json.hpp includes/rz_config.hpp
  includes/rz_photo-gallery_plugins.hpp)

add_executable(test_write test_write.cpp includes/rz_config.hpp
                          includes/rz_photo-gallery_plugins.hpp)
target_compile_features(test_write PUBLIC cxx_std_23)
target_link_libraries(test_write PRIVATE Qt6::Core nlohmann_json::nlohmann_json)

add_executable(test_read test_read.cpp includes/rz_config.hpp)
target_compile_features(test_read PUBLIC cxx_std_23)
target_link_libraries(test_read PRIVATE Qt6::Core nlohmann_json::nlohmann_json)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core
                                              nlohmann_json::nlohmann_json)

target_compile_definitions(${PROJECT_NAME} PRIVATE RZ_WRITE_JSON_LIBRARY)

# the end
message(
  "Build with CMake version: ${CMAKE_VERSION} and ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} c++${CMAKE_CXX_STANDARD} QT ${CMAKE_QTV}"
)
include(ProcessorCount)
ProcessorCount(N)
message("number of processors: " ${N})
message("cmake --build . --parallel ${N}")
