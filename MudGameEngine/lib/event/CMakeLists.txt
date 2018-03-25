add_library(event
        Event.cpp)

set_target_properties(event
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14)

install(TARGETS	event
        ARCHIVE DESTINATION lib)