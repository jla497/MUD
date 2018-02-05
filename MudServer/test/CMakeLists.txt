add_subdirectory(lib/googlemock)
enable_testing()

add_executable(mudtest
        ConnectionManagerTests.cpp
        GameManagerTests.cpp
        ParserTests.cpp
        CommandParserTests.cpp)

set_target_properties(mudtest
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 14
)
target_link_libraries(mudtest gmock gtest gtest_main)
target_link_libraries(mudtest connectionmanager)
target_link_libraries(mudtest gamemanager)
target_link_libraries(mudtest entity)
target_link_libraries(mudtest parser)
target_link_libraries(mudtest reset)

target_link_libraries(mudtest commandparser)
add_test(ConnectionManagerTests mudtest)
add_test(GameManagerTests mudtest)
add_test(ParserTests mudtest)
add_test(CommandParserTests mudtest)

include_directories(include)