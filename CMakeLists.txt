cmake_minimum_required(VERSION 3.10.0)
project(snake VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)

add_executable(snake main.cpp)

target_link_libraries(snake PRIVATE fmt::fmt)
target_sources(snake PRIVATE src/ui.cpp src/geo.cpp)
target_include_directories(snake PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/inc)
