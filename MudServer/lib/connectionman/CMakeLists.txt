
add_library(connectionman ConnectionManager.cpp ConnectionContainer.cpp)

set_target_properties(connectionman
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)


install(TARGETS connectionman
  ARCHIVE DESTINATION lib
)

