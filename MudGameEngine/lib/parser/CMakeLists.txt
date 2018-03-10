
add_library(parser 
	YamlParser.cpp
	SpellParser.cpp
        parser.cpp)

set_target_properties(parser
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14)


target_link_libraries(parser yaml-cpp)
target_link_libraries(parser entity)
target_link_libraries(parser uniqueid)
target_link_libraries(parser reset)
target_link_libraries(parser spells)
target_link_libraries(parser factory)

install(TARGETS parser ARCHIVE DESTINATION lib)

