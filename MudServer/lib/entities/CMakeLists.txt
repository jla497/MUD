
add_library(dummyentity DummyEntity.cpp)

set_target_properties(dummyentity
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)


install(TARGETS dummyentity
  ARCHIVE DESTINATION lib
)

