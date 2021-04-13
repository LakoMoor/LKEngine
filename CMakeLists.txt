cmake_minimum_required(VERSION 3.0.0)
project(LKEngine VERSION 0.2.0)

add_executable(LKEngine src/main.cpp src/Core src/Discord/Discord.cpp src/Discord/Discord.hpp src/Core/Game.cpp src/Core/Game.hpp src/Player/view.hpp)

add_subdirectory(lib/SFML)
add_subdirectory(lib/discord-rpc)

#SFML
include_directories(lib/SFML/include)
link_directories(lib/SFML/lib)
#DiscordRPC
include_directories(lib/discord-rpc/include)
link_directories(lib/discord-rpc/lib)

set(EXECUTABLE_OUTPUT_PATH "bin")


#find_package(SFML COMPONENTS system window graphics network audio)

target_link_libraries (LKEngine discord-rpc sfml-graphics sfml-window sfml-network sfml-system sfml-audio)
