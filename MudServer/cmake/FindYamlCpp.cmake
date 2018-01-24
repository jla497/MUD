# Set up yaml-cpp library
set(FIND_YAMLCPP_PATHS ${CMAKE_SOURCE_DIR}/yaml-cpp)

find_path(YAMLCPP_INCLUDE_DIR yaml.header
            PATH_SUFFIXES include
            PATHS ${FIND_YAMLCPP_PATHS})

find_library(YAMLCPP_LIBRARY
            NAMES yaml-cpp
            PATH_SUFFIXES lib
            PATHS ${FIND_YAMLCPP_PATHS})