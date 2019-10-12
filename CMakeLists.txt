cmake_minimum_required(VERSION 3.2)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)

include_directories($ENV{TOOLS_INCLUDE} ${CMAKE_SOURCE_DIR}/include)

# Add terminal sub directory
add_subdirectory(terminal)


set(SRC_LIST
        src/main.cpp
        include/Cell_Culture/Cell.h include/Support/FileLoader.h include/GameOfLife.h include/Support/Globals.h include/Support/MainArgumentsParser.h include/Cell_Culture/Population.h include/GoL_Rules/RuleFactory.h include/GoL_Rules/RuleOfExistence.h include/ScreenPrinter.h src/Cell_Culture/Cell.cpp src/Support/FileLoader.cpp src/GameOfLife.cpp src/Support/Globals.cpp src/Cell_Culture/Population.cpp src/GoL_Rules/RuleFactory.cpp src/GoL_Rules/RuleOfExistence.cpp src/ScreenPrinter.cpp include/GoL_Rules/RuleOfExistence_Conway.h src/GoL_Rules/RuleOfExistence_Conway.cpp include/GoL_Rules/RuleOfExistence_VonNeumann.h src/GoL_Rules/RulesOfExistence_VonNeumann.cpp include/GoL_Rules/RuleOfExistence_Erik.h src/GoL_Rules/RuleOfExistence_Erik.cpp include/Support/SupportStructures.h src/Support/MainArgumentsParser.cpp include/Support/MainArguments.h src/Support/MainArguments.cpp)


# Om Debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Debug mode
    message("Debug mode")
    add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Test")
    # Skriv ut medelande Test mode.
    message("Test mode")
    list(REMOVE_ITEM SRC_LIST "src/main.cpp")
    aux_source_directory(./test SRC_LIST)
else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Release mode.
    message("Release mode")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} Terminal)