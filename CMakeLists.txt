cmake_minimum_required( VERSION 2.8 )

project(Laba)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(googletest)
include_directories( include )
add_subdirectory( sample )
add_subdirectory( tests )
include_directories(${CMAKE_SOURCE_DIR})
