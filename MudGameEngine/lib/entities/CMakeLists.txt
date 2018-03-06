add_library(entity Entity.cpp
	   	 DoorEntity.cpp
		 RoomEntity.cpp
		 CharacterEntity.cpp		 
		 ObjectEntity.cpp
		 AreaEntity.cpp
		 ShopEntity.cpp
		 CombatComponent.cpp)

add_library(uniqueid UniqueId.cpp)

set_target_properties(
	uniqueid
	entity
		PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 14
)

target_link_libraries(entity uniqueid administrator)

install(TARGETS 
	uniqueid
	entity
		ARCHIVE DESTINATION lib
)

