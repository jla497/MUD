add_subdirectory(lib/googlemock)
enable_testing()

add_executable(mudtest
        ConnectionManagerTests.cpp
        GameManagerTests.cpp
        )
set_target_properties(mudtest
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)
target_link_libraries(mudtest gmock gtest gtest_main)
target_link_libraries(mudtest connectionman)
target_link_libraries(mudtest gamemanager)
add_test(ConnectionManagerTests mudtest)
add_test(GameManagerTests mudtest)


