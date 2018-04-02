add_library(states
        IState.cpp
        WaitState.cpp
        InteractState.cpp
        Dialogue.cpp)

set_target_properties(states
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14)

target_link_libraries(states entity controllers gamemanager)

install(TARGETS	states
        ARCHIVE DESTINATION lib)