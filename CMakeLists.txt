cmake_minimum_required(VERSION 3.0.0)
project(LKEngine VERSION 0.1.0)

add_executable(LKEngine src/main.cpp src/Core src/Core/Game.cpp src/Core/Game.hpp src/Player/view.hpp)

#add_subdirectory(lib/SFML)
set(SFML_DIR "lib/SFML")
include_directories("lib/SFML/include")

set(EXECUTABLE_OUTPUT_PATH "bin")


find_package(SFML COMPONENTS system window graphics network audio)
target_link_libraries (LKEngine  sfml-graphics sfml-window sfml-network sfml-system sfml-audio)
