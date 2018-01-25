cmake_minimum_required(VERSION 3.2)
project(ChatExample)

set(PACKAGE_NAME ChatExample)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "wsumner@sfu.ca")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# And the project header and library paths
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${LIBRARY_OUTPUT_PATH})
set(CMAKE_TEMP_LIBRARY_PATH "${PROJECT_BINARY_DIR}/lib")

add_subdirectory(lib)
add_subdirectory(tools)


# link yaml-cpp library

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(project_yamlcpp
  GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp.git"
  GIT_TAG "master"
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  PREFIX=${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp
)

ExternalProject_Get_Property(project_yamlcpp install_dir)

add_library(yaml-cpp STATIC IMPORTED)

set_property(TARGET yaml-cpp PROPERTY IMPORTED_LOCATION ${install_dir}/lib/yaml-cpp)

add_dependencies(yaml-cpp project_yamlcpp)




