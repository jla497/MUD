cmake_minimum_required(VERSION 3.2)
project(MudServer)

set(PACKAGE_NAME MudServer)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -Wno-deprecated-declarations is for boost use of auto_ptr
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-declarations -std=c++14")

link_directories(${LIBRARY_OUTPUT_PATH})

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(tools)
