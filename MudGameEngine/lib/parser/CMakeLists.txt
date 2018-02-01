find_package(yaml-cpp)
add_library(parser YamlParser.cpp)

set_target_properties(parser
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14)


target_link_libraries(parser yaml-cpp)
target_link_libraries(entity Entity.cpp)
target_link_libraries(doorentity DoorEntity.cpp)
target_link_libraries(roomentity RoomEntity.cpp)
target_link_libraries(npcentity NPCEntity.cpp)
target_link_libraries(objectentity ObjectEntity.cpp)
target_link_libraries(areaentity AreaEntity.cpp)
target_link_libraries(shopentity ShopEntity.cpp)

install(TARGETS parser ARCHIVE DESTINATION lib)

