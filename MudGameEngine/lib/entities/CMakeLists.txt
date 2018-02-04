add_library(entity Entity.cpp
	   	 DoorEntity.cpp
		 RoomEntity.cpp
		 CharacterEntity.cpp		 
		 NPCharacterEntity.cpp
		 PlayerCharacterEntity.cpp
		 ObjectEntity.cpp
		 AreaEntity.cpp
		 ShopEntity.cpp)

add_library(reset Reset.cpp)

set_target_properties(
	entity
	reset
		PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 14
)

install(TARGETS 
	entity
	reset
		ARCHIVE DESTINATION lib
)

