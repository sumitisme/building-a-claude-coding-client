cmake_minimum_required(VERSION 3.10)

project(claude-code-app VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(cpr REQUIRED)

target_link_libraries(
    claude-code
    PRIVATE
    cpr::cpr
    nlohmann_json::nlohmann_json
)