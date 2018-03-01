add_library(entity Entity.cpp
	   	 DoorEntity.cpp
		 RoomEntity.cpp
		 CharacterEntity.cpp		 
		 ObjectEntity.cpp
		 AreaEntity.cpp
		 ShopEntity.cpp)

add_library(uniqueid UniqueId.cpp)

add_library(reset Reset.cpp)

set_target_properties(
	uniqueid
	entity
	reset
		PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 14
)

target_link_libraries(entity uniqueid)

install(TARGETS 
	uniqueid
	entity 
	reset
		ARCHIVE DESTINATION lib
)

