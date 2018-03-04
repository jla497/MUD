add_library(resources commands.cpp
                      playercharacterdefaults.cpp)

set_target_properties(resources
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14
        )

install(TARGETS resources
        ARCHIVE DESTINATION lib
        )