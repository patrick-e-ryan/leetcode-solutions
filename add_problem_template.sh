#!/bin/bash

set -e
set -x

problem_name=$1

dir_name="$(pwd)/src/$problem_name"


mkdir "$dir_name"

cp "$(pwd)"/src/template/* "$dir_name"

{ 
    printf "%s\n" "add_executable($problem_name driver.cpp solution.cpp)";
    printf "%s\n" "target_include_directories($problem_name PRIVATE \$<BUILD_INTERFACE:\${CMAKE_CURRENT_SOURCE_DIR}>)";
    printf "%s\n" "target_link_libraries($problem_name PRIVATE nlohmann_json::nlohmann_json)";
    printf "%s\n" "target_compile_features($problem_name PRIVATE cxx_std_23)";
}  >> "$dir_name/CMakeLists.txt"
