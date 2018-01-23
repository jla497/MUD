
add_executable(connmantest
  connmantest.cpp
)

target_link_libraries(connmantest networking)
target_link_libraries(connmantest connectionman)
target_link_libraries(connmantest handlers)
target_link_libraries(connmantest protocols)

set_target_properties(connmantest
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
                      PREFIX ""
)

# This program requires boost
find_package(Boost 1.58 COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(connmantest ${Boost_LIBRARIES})

install(TARGETS connmantest
  RUNTIME DESTINATION bin
)

