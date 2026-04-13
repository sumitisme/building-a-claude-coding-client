cmake_minimum_required(VERSION 3.10)

project(claude-code-app VERSION 1.0)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

add_executable(claoude_code ${SOURCE_FILES})
add_executable(cpr REQUIRED)

target_link_libraries(
    claude-code PRIVATE
    cpr::cpr
    nlohmann_json::nlohmann_json
)