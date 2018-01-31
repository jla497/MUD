
add_library(connectionman ConnectionManager.cpp ConnectionContainer.cpp)

find_package(Boost 1.58 COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set_target_properties(connectionman
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

target_link_libraries(connectionman networking)
target_link_libraries(connectionman protocols)
target_link_libraries(connectionman ${Boost_LIBRARIES})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

install(TARGETS connectionman ARCHIVE DESTINATION lib)

