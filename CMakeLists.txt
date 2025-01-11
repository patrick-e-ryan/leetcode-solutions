cmake_minimum_required(VERSION 3.23...3.31)

project(
    leetcode_solutions
    LANGUAGES CXX
)

# Disable tests in nlohmann_json.
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(third_party/json)

add_subdirectory(src)
