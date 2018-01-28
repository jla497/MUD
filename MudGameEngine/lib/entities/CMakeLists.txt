
add_library(roomentity RoomEntity.cpp)
add_library(entity Entity.cpp)

set_target_properties(roomentity entity
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)


install(TARGETS roomentity entity
  ARCHIVE DESTINATION lib
)

