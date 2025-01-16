add_executable(2429_minimize_xor driver.cpp solution.cpp)
target_include_directories(2429_minimize_xor PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(2429_minimize_xor PRIVATE nlohmann_json::nlohmann_json)
target_compile_features(2429_minimize_xor PRIVATE cxx_std_23)
