add_subdirectory(lib/googlemock)
enable_testing()

add_executable(connectionmantest
  # Add all new test files to the list here.
  # Place each file name on a separate line.
  ConnectionManagerTests.cpp
)

#find_package(Boost 1.58 COMPONENTS system REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#target_link_libraries(connectionmantest ${Boost_LIBRARIES})

target_link_libraries(connectionmantest gmock gtest gtest_main)
#target_link_libraries(connectionmantest networking)
target_link_libraries(connectionmantest connectionman)
#target_link_libraries(connectionmantest protocols)

add_test(NAME AllTests COMMAND connectionmantest)

