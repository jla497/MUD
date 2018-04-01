add_library(actions
	Action.cpp
	DecoyAction.cpp
	CharacterModAction.cpp
	SayAction.cpp
	MoveAction.cpp
	AttackAction.cpp
	NullAction.cpp
	LookAction.cpp
	CastAction.cpp
	PrgmAction.cpp
	SaveAction.cpp
    TimedAction.cpp
	HaltAction.cpp
	SwapAction.cpp)
	TakeAction.cpp)

set_target_properties(actions
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 14)

target_link_libraries(actions gamemanager combatsim entity)

install(TARGETS	actions
		ARCHIVE DESTINATION lib)
