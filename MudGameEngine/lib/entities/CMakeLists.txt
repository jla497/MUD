
add_library(roomentity RoomEntity.cpp)

set_target_properties(roomentity
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)


install(TARGETS roomentity
  ARCHIVE DESTINATION lib
)

