
add_library(connectionmanager ConnectionManager.cpp 
			  ConnectionContainer.cpp
			  MudProtocol.cpp)

find_package(Boost 1.58 COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set_target_properties(connectionmanager
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
		     )

target_link_libraries(connectionmanager networking)
target_link_libraries(connectionmanager ${Boost_LIBRARIES})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

install(TARGETS connectionmanager ARCHIVE DESTINATION lib)

