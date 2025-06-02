cmake_minimum_required(VERSION 3.16)
project(Chess LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB TEMPLATE_SRC CONFIGURE_DEPENDS
        tel-hai-excellenteam-*/Chess/src/*.cpp)

list(FILTER TEMPLATE_SRC EXCLUDE REGEX ".*/main.cpp$")
list(FILTER PROJECT_SRC EXCLUDE REGEX ".*/MoveRecommender_helpers.cpp$")

file(GLOB PROJECT_SRC CONFIGURE_DEPENDS src/*.cpp)

add_executable(chess_multithread ${PROJECT_SRC} ${TEMPLATE_SRC})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(chess_multithread PRIVATE Threads::Threads)