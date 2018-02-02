
add_library(entity Entity.cpp)
add_library(doorentity DoorEntity.cpp)
add_library(roomentity RoomEntity.cpp)
add_library(npcentity NPCEntity.cpp)
add_library(objectentity ObjectEntity.cpp)
add_library(areaentity AreaEntity.cpp)
add_library(shopentity ShopEntity.cpp)
add_library(reset Reset.cpp)

add_library(actions 
SayAction.cpp
MoveAction.cpp
AttackAction.cpp
)

set_target_properties(entity 
	doorentity
	npcentity 
	objectentity 
	roomentity 
	areaentity 
	shopentity
	reset
	actions
		PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 14
)

target_link_libraries(actions gamemanager)

install(TARGETS 
	entity 
	doorentity
	npcentity 
	objectentity 
	roomentity 
	areaentity 
	shopentity
	reset
	actions
		ARCHIVE DESTINATION lib
)

