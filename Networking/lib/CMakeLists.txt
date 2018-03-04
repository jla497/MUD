add_library(networking
  Server.cpp
  Client.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(networking Threads::Threads)

set_target_properties(networking
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

install(TARGETS networking
  ARCHIVE DESTINATION lib
)

