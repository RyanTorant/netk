cmake_minimum_required(VERSION 3.6.2)
project(netk)

add_subdirectory(boost-cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(project_sources src/primitives/Node.cpp
)

add_library(netk_lib STATIC ${project_sources})
target_link_libraries(netk_lib Boost::serialization)