
add_library(i18n i18n.cpp)

set_target_properties(i18n PROPERTIES CXX_STANDARD 14)

target_link_libraries(i18n yaml-cpp)

install(TARGETS i18n ARCHIVE DESTINATION lib)
