find_package(yaml-cpp)
add_library(parser YamlParser.cpp)

set_target_properties(parser
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14)


target_link_libraries(parser yaml-cpp)
target_link_libraries(parser entity)
target_link_libraries(parser uniqueid)

install(TARGETS parser ARCHIVE DESTINATION lib)

