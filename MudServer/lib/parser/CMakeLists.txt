
add_library(parser YamlParser.cpp)

set_target_properties(parser
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14)

include_directories(${install_dir}/include/yaml-cpp/include/yaml-cpp)

target_link_libraries(parser yaml-cpp)

install(TARGETS parser ARCHIVE DESTINATION lib)

