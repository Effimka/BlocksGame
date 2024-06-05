cmake_minimum_required(VERSION 3.0)

project(PhenomenGames)

set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/lib/SFML-2.6.1)
set(CMAKE_BUILD_TYPE Release)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)


file(GLOB srcs
   "src/*.h"
   "src/*.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} ${srcs})

target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-window sfml-system)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Copying debug DLLs...")
    file(COPY ${CMAKE_SOURCE_DIR}/lib/SFML-2.6.1/bin/ DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_BINARY_DIR})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Copying release DLLs...")
    file(COPY ${CMAKE_SOURCE_DIR}/lib/SFML-2.6.1/bin/ DESTINATION ${CMAKE_BINARY_DIR}/Release)
    file(COPY ${CMAKE_SOURCE_DIR}/resource/ DESTINATION ${CMAKE_BINARY_DIR}/Release)
else()
    message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

