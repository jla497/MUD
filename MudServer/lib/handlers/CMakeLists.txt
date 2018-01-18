
add_library(handlers PlayHandler.cpp LoginHandler.cpp)

set_target_properties(handlers
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)



install(TARGETS handlers
  ARCHIVE DESTINATION lib
)

