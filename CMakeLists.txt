cmake_minimum_required(VERSION 3.2)
project(Adventure2018)

set(PACKAGE_NAME Adventure2018)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
# set(PACKAGE_BUGREPORT "bugs@example.com")

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/MudServer/include)
include_directories(${CMAKE_SOURCE_DIR}/MudGameEngine/include)

add_subdirectory(MudServer)
add_subdirectory(MudGameEngine)

