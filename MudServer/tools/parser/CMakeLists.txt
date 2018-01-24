
# append instructions on how to find yaml-cpp library
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_executable(parsertest parsertest.cpp)
set_property(TARGET parsertest PROPERTY CXX_STANDARD 14)
target_link_libraries(parsertest parser)
set_property(TARGET parser PROPERTY CXX_STANDARD 14)

include(FindPkgConfig)
find_package(yaml-cpp REQUIRED)
include_directories(${YAMLCPP_INCLUDE_DIR})
target_link_libraries(parsertest ${YAMLCPP_LIBRARY})

install (TARGETS parsertest DESTINATION bin)