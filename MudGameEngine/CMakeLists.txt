cmake_minimum_required(VERSION 3.2)
project(MudGameEngine)

set(PACKAGE_NAME MudGameEngine)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# And the project header and library paths
link_directories(${LIBRARY_OUTPUT_PATH})

add_subdirectory(lib)
add_subdirectory(tools)


# link yaml-cpp library


add_library(yaml-cpp STATIC IMPORTED)

add_dependencies(yaml-cpp project_yamlcpp)
