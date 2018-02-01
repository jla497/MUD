find_package(yaml-cpp)
add_library(parser YamlParser.cpp)

set_target_properties(parser
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14)


target_link_libraries(parser yaml-cpp)
target_link_libraries(parser entity)
target_link_libraries(parser doorentity)
target_link_libraries(parser roomentity)
target_link_libraries(parser npcentity)
target_link_libraries(parser objectentity)
target_link_libraries(parser areaentity)
target_link_libraries(parser shopentity)

install(TARGETS parser ARCHIVE DESTINATION lib)

