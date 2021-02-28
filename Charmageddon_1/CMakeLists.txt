cmake_minimum_required(VERSION 3.17)
project(Charmageddon_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Charmageddon_1 main.cpp GameState.cpp GameState.hpp Map.cpp Map.hpp Player.cpp Player.hpp InteractableObject.cpp InteractableObject.hpp Obstacle.cpp Obstacle.hpp Bonus.cpp Bonus.hpp Menu.cpp Menu.hpp)