add_library(combatsim CombatSimulation.cpp)

set_target_properties(combatsim
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14)


target_link_libraries(combatsim entity gamemanager)

