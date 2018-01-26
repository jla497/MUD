add_subdirectory(lib/googlemock)
enable_testing()

add_executable(runAllTests
  # Add all new test files to the list here.
  # Place each file name on a separate line.
  ConnectionManagerTests.cpp
)

#find_package(Boost 1.58 COMPONENTS system REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#target_link_libraries(runAllTests ${Boost_LIBRARIES})

target_link_libraries(runAllTests gmock gtest gtest_main)
#target_link_libraries(runAllTests networking)
target_link_libraries(runAllTests connectionman)
#target_link_libraries(runAllTests protocols)

add_test(NAME AllTests COMMAND runAllTests)

