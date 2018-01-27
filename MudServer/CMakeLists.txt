cmake_minimum_required(VERSION 3.2)
project(Adventure2018)

set(PACKAGE_NAME Adventure2018)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
# set(PACKAGE_BUGREPORT "bugs@example.com")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -Wno-deprecated-declarations is for boost use of auto_ptr
set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -fno-rtti -Wno-deprecated-declarations -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# And the project header and library paths
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${LIBRARY_OUTPUT_PATH})
set(CMAKE_TEMP_LIBRARY_PATH "${PROJECT_BINARY_DIR}/lib")

add_subdirectory(lib)
add_subdirectory(tools)


