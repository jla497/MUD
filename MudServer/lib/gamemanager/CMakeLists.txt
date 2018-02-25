add_library(gamemanager
    GameManager.cpp
    GameState.cpp
    Player.cpp
    LutBuilder.cpp
        PlayerService.cpp ../../include/gamemanager/PlayerService.h)

target_link_libraries(gamemanager
    connectionmanager
    logging
    entity
    commandparser
)

set_target_properties(gamemanager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

install(TARGETS gamemanager
  ARCHIVE DESTINATION lib
)
