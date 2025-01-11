add_executable(0127_word_ladder driver.cpp solution.cpp)
target_include_directories(0127_word_ladder PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(0127_word_ladder PRIVATE nlohmann_json::nlohmann_json)
target_compile_features(0127_word_ladder PRIVATE cxx_std_23)