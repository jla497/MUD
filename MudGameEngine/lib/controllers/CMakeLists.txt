add_library(controllers
        CharacterController.cpp
        AiController.cpp
        PlayerController.cpp)

set_target_properties(controllers
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14)

target_link_libraries(controllers entity states gamemanager event)

install(TARGETS	controllers
        ARCHIVE DESTINATION lib)
