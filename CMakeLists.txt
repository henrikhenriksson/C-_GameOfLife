cmake_minimum_required(VERSION 3.2)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)

#include tools used
include_directories($ENV{TOOLS_INCLUDE} ${CMAKE_SOURCE_DIR}/include)

# Add terminal project sub directory
add_subdirectory(terminal)

#Add header files
include_directories(./include)

#Add program sources
aux_source_directory(./src SRC_LIST)
aux_source_directory(./src/Cell_Culture SRC_LIST)
aux_source_directory(./src/GoL_Rules SRC_LIST)
aux_source_directory(./src/Support SRC_LIST)

#use debug as standard
add_definitions(-DDEBUG)

#Add test files
aux_source_directory(./test SRC_LIST_TEST)
#include program files when building test
list(APPEND SRC_LIST_TEST ${SRC_LIST})
#Remove program main for program not to get conflict of multiple main files
list(REMOVE_ITEM SRC_LIST_TEST "./src/main.cpp")

#build program and test
add_executable(${PROJECT_NAME}_TEST ${SRC_LIST_TEST})
add_executable(${PROJECT_NAME} ${SRC_LIST})

#Link to terminal project
target_link_libraries(${PROJECT_NAME} Terminal)
target_link_libraries(${PROJECT_NAME}_TEST Terminal)