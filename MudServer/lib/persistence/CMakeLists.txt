add_library(persistence PersistenceService.cpp)

set_target_properties(persistence
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14
        )

# This program requires boost
find_package(Boost 1.58 COMPONENTS system filesystem serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(persistence ${Boost_LIBRARIES} gamemanager)

install(TARGETS persistence
        ARCHIVE DESTINATION lib
        )