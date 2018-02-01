add_library(gamemanager
    GameManager.cpp
    GameState.cpp
    Character.cpp
    Player.cpp
    Room.cpp
)

target_link_libraries(gamemanager
        connectionman
        commandparser)

set_target_properties(gamemanager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

install(TARGETS gamemanager
  ARCHIVE DESTINATION lib
)
