cmake_minimum_required(VERSION 3.24)
project(Project1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Project1 main.cpp src/Manager.cpp src/Manager.h src/Graph.cpp src/Graph.h src/Station.cpp src/Station.h src/Network.cpp src/Network.h)
