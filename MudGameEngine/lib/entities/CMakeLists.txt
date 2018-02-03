
add_library(uniqueid UniqueId.cpp)
add_library(entity Entity.cpp
 				   	 DoorEntity.cpp
					 RoomEntity.cpp
					 NPCEntity.cpp
					 ObjectEntity.cpp
					 AreaEntity.cpp
					 ShopEntity.cpp)

add_library(reset Reset.cpp)
add_library(actions 
SayAction.cpp
MoveAction.cpp
AttackAction.cpp
)

set_target_properties( uniqueid
	entity 
	reset
	actions
		PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 14
)

target_link_libraries(entity uniqueid)
target_link_libraries(actions gamemanager)

install(TARGETS 
	uniqueid
	entity 
	reset
	actions
		ARCHIVE DESTINATION lib
)

