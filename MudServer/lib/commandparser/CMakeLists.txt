add_library(commandparser CommandParser.cpp)

set_target_properties(commandparser
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

find_package(Boost 1.58 COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(commandparser ${Boost_LIBRARIES})

install(TARGETS commandparser ARCHIVE DESTINATION lib)

