add_library(observer
        ActionObserver.cpp)

set_target_properties(observer
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14)

install(TARGETS	observer
        ARCHIVE DESTINATION lib)