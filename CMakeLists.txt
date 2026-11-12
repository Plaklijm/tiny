cmake_minimum_required(VERSION 4.4)
project(tiny LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/Dependencies.cmake)
enable_testing()
add_subdirectory(app)
add_subdirectory(math)
add_subdirectory(tests)
add_executable(tiny main.cpp)
