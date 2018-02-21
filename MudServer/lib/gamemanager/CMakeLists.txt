add_library(gamemanager
    GameManager.cpp
    GameState.cpp
    Player.cpp
    LutBuilder.cpp
)

add_library(factory EntityFactory.cpp)
target_link_libraries(factory logging
            entity
)

target_link_libraries(gamemanager
    connectionmanager
    logging
    entity
    commandparser
    reset
    factory
)

set_target_properties(gamemanager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

install(TARGETS gamemanager
  ARCHIVE DESTINATION lib
)
