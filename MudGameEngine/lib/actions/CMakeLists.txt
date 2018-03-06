add_library(actions
	Action.cpp
	SayAction.cpp
	MoveAction.cpp
	AttackAction.cpp
	NullAction.cpp
	LookAction.cpp
	SwapAction.cpp
	PrgmAction.cpp
	SaveAction.cpp
    TimedAction.cpp)

set_target_properties(actions
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 14)

target_link_libraries(actions gamemanager resources combatsim entity)

install(TARGETS	actions
		ARCHIVE DESTINATION lib)
