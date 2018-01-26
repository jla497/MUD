find_package(yaml-cpp)
add_executable(parsertest parsertest.cpp)
set_property(TARGET parsertest PROPERTY CXX_STANDARD 14)
target_link_libraries(parsertest parser)
set_property(TARGET parser PROPERTY CXX_STANDARD 14)


target_link_libraries(parsertest yaml-cpp)

install (TARGETS parsertest DESTINATION bin)
