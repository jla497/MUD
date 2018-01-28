
add_library(protocols MudProtocol.cpp)

set_target_properties(protocols
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

install(TARGETS protocols
  ARCHIVE DESTINATION lib
)

