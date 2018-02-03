add_library(logging
        logging.cpp
        ConsoleLogger.cpp
)

set_target_properties(logging
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 14
)

install(TARGETS logging
  ARCHIVE DESTINATION lib
)
