cmake_minimum_required(VERSION 3.20)
project(tank-battle)

add_library(engine "" "")
target_include_directories(engine PUBLIC engine)
target_sources(engine PRIVATE engine/engine.c)

add_executable(tankbattle "" "")
target_include_directories(tankbattle PRIVATE tankbattle)
target_sources(tankbattle PRIVATE
	tankbattle/tankbattle.c
        tankbattle/calc.c
)
target_link_libraries(tankbattle SDL2 m engine)

# tests
add_subdirectory(unity)

add_executable(test-calc tests/calc.c tankbattle/calc.c)
target_include_directories(test-calc PRIVATE tankbattle)
target_link_libraries(test-calc PRIVATE unity m)

add_executable(test-engine tests/engine.c)
target_link_libraries(test-engine PRIVATE unity SDL2 engine)

include(CTest)
add_test(NAME calc COMMAND test-calc)
add_test(NAME engine COMMAND test-engine)
