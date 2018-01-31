cmake_minimum_required(VERSION 3.2)
project(Adventure2018)

set(PACKAGE_NAME Adventure2018)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
# set(PACKAGE_BUGREPORT "bugs@example.com")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")


include_directories(${CMAKE_SOURCE_DIR}/MudServer/include)
include_directories(${CMAKE_SOURCE_DIR}/MudGameEngine/include)

add_subdirectory(MudServer)
add_subdirectory(MudGameEngine)

