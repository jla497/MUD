cmake_minimum_required(VERSION 3.2)
project(Adventure2018)

set(PACKAGE_NAME Adventure2018)
set(PACKAGE_VERSION 0.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
# set(PACKAGE_BUGREPORT "bugs@example.com")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-expansion-to-defined")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer \
    -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr \
    -fsanitize-address-use-after-scope -fno-limit-debug-info")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -march=native")

add_subdirectory(googletest/googlemock)

include_directories(${CMAKE_SOURCE_DIR}/MudServer/include)
include_directories(${CMAKE_SOURCE_DIR}/MudGameEngine/include)
include_directories(${CMAKE_SOURCE_DIR}/Networking/include)
include_directories(${CMAKE_SOURCE_DIR}/Client/include)
include_directories(${CMAKE_SOURCE_DIR}/Logging/include)

add_subdirectory(Networking)
add_subdirectory(MudGameEngine)
add_subdirectory(MudServer)
add_subdirectory(Client)
add_subdirectory(Logging)
add_subdirectory(test)
add_subdirectory(locales)

configure_file(config.yaml config.yaml COPYONLY)
