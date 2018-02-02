
add_library(uniqueid UniqueId.cpp)
add_library(entity Entity.cpp
 				   	 DoorEntity.cpp
					 RoomEntity.cpp
					 NPCEntity.cpp
					 ObjectEntity.cpp
					 AreaEntity.cpp
					 ShopEntity.cpp)

add_library(reset Reset.cpp)
add_library(sayaction SayAction.cpp)
add_library(moveaction MoveAction.cpp)
add_library(attackaction AttackAction.cpp)
set_target_properties( uniqueid
	entity 
	reset
	sayaction
	moveaction
	attackaction
		PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 14
)

target_link_libraries(entity uniqueid)
target_link_libraries(sayaction gamemanager)
target_link_libraries(moveaction gamemanager)
target_link_libraries(attackaction gamemanager)

install(TARGETS 
	uniqueid
	entity 
	reset
	sayaction
	moveaction
	attackaction
		ARCHIVE DESTINATION lib
)

