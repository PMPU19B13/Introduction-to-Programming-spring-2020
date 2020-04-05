cmake_minimum_required(VERSION 3.15)
project(itp_project)

set(CMAKE_CXX_STANDARD 20)

set(SFML_INCLUDE_DIR ../sfml_linux/include)
set(SFML_LIBRARY_DIR ../sfml_linux/lib)
set(SFML_DIR ../sfml_linux/lib/cmake/SFML)

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
include_directories(../include)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(itp_project ../src/main.cpp ../src/geometry.cpp ../src/id.cpp ../src/controller.cpp ../src/drawer.cpp)

target_link_libraries(itp_project sfml-graphics sfml-window sfml-system)