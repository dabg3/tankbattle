cmake_minimum_required(VERSION 3.20)
project(tank-battle)

#TODO check unity test framework for how to include
#add_library(engine STATIC "")
#target_include_directories(engine PUBLIC engine)
#target_sources(engine PRIVATE engine/engine.c)

add_executable(tankbattle "" "")
target_include_directories(tankbattle PRIVATE tankbattle PRIVATE engine)
target_sources(tankbattle PRIVATE
        engine/engine.c
        engine/game.c
	tankbattle/tankbattle.c
        tankbattle/calc.c
)
target_link_libraries(tankbattle SDL2 m)
#target_link_libraries(tankbattle SDL2 m engine)

# tests
add_subdirectory(unity)

add_executable(test-calc tests/calc.c tankbattle/calc.c)
target_include_directories(test-calc PRIVATE tankbattle)
target_link_libraries(test-calc PRIVATE unity m)

add_executable(test-engine tests/engine.c engine/engine.c)
target_include_directories(test-engine PRIVATE engine)
target_link_libraries(test-engine PRIVATE unity SDL2 m)

include(CTest)
add_test(NAME calc COMMAND test-calc)
add_test(NAME engine COMMAND test-engine)
