add_library(administrator Administrator.cpp)

set_target_properties(administrator
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14
        )

add_library(factory EntityFactory.cpp)
target_link_libraries(factory logging
        entity
        )

set_target_properties(factory
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14
        )

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
    reset
    factory
    administrator
)

set_target_properties(gamemanager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

install(TARGETS gamemanager
                administrator
                factory
        ARCHIVE DESTINATION lib
)
