cmake_minimum_required(VERSION 3.8)
project(osu_pattern)
set(CMAKE_CXX_STANDARD 11)
set(BUILD_LIBRARY true)

add_subdirectory(../osupp "${CMAKE_CURRENT_BINARY_DIR}/osupp")
include_directories(../osupp)

set(SOURCE_FILES main.cpp iterator.cpp math.cpp osu_extensions.cpp utils.cpp patterns.cpp)
add_executable(osu_pattern ${SOURCE_FILES})

target_link_libraries(osu_pattern PRIVATE osupp)