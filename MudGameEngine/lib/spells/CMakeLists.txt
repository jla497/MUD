add_library(spells
	Spell.cpp)

set_target_properties(actions
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 14)

install(TARGETS	spells
		ARCHIVE DESTINATION lib)
