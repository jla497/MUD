add_library(reset Reset.cpp ResetManager.cpp)

set_target_properties(
        reset
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14
)

target_link_libraries(reset gamemanager
        parser
        factory)

install(TARGETS
        reset
        ARCHIVE DESTINATION lib
        )
