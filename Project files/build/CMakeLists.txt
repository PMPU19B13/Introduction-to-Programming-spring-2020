cmake_minimum_required(VERSION 3.15)
project(itp_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(../include)
add_executable(itp_project ../src/main.cpp ../src/geometry.cpp ../src/id.cpp ../src/controller.cpp ../src/drawer.cpp)