
add_library(roomentity RoomEntity.cpp)
add_library(entity Entity.cpp)
add_library(npcentity NPCEntity.cpp)
add_library(resetentity ResetEntity.cpp)

set_target_properties(roomentity entity npcentity resetentity
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)


install(TARGETS roomentity entity npcentity resetentity
  ARCHIVE DESTINATION lib
)

