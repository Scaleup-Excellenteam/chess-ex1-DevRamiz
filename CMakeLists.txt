cmake_minimum_required(VERSION 3.15)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(chess_lib)

add_executable(chess main.cpp)

target_link_libraries(chess PRIVATE chess_lib)

add_subdirectory(include)
add_subdirectory(src)

option(ENABLE_TESTING "Build unit tests" ON)
if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()