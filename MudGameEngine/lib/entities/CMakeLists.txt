add_library(entity Entity.cpp
	   	 DoorEntity.cpp
		 RoomEntity.cpp
		 CharacterEntity.cpp
		 NPCEntity.cpp
		 PlayerCharacterEntity.cpp
		 ObjectEntity.cpp
		 AreaEntity.cpp
		 ShopEntity.cpp)

add_library(reset Reset.cpp)

add_library(actions 
SayAction.cpp
MoveAction.cpp
AttackAction.cpp
)

set_target_properties( 
	entity 
	reset
	actions
		PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 14
)

target_link_libraries(actions gamemanager)

install(TARGETS 
	entity 
	reset
	actions
		ARCHIVE DESTINATION lib
)

