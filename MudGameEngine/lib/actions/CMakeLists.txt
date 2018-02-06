add_library(actions
	Action.cpp
	SayAction.cpp
	MoveAction.cpp
	AttackAction.cpp
	NullAction.cpp
	LookAction.cpp)

set_target_properties(actions
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 14)

target_link_libraries(actions gamemanager)

install(TARGETS	actions
		ARCHIVE DESTINATION lib)

