add_executable(mudserver
  mudserver.cpp
)

target_link_libraries(mudserver networking)
target_link_libraries(mudserver connectionmanager)
target_link_libraries(mudserver gamemanager)
target_link_libraries(mudserver -lpthread)


set_target_properties(mudserver
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
                      PREFIX ""
)

# This program requires boost
find_package(Boost 1.58 COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(mudserver ${Boost_LIBRARIES})

install(TARGETS mudserver
  RUNTIME DESTINATION bin
)

