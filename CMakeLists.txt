cmake_minimum_required(VERSION 3.20)
project(tank-battle)

add_executable(tankbattle "" "")
target_include_directories(tankbattle PRIVATE include)
target_sources(tankbattle PRIVATE
	src/tankbattle.c
        src/calc.c
)
target_link_libraries(tankbattle SDL2 m)

# tests
add_subdirectory(unity)

add_executable(test-calc tests/calc.c src/calc.c)
target_include_directories(test-calc PRIVATE include)
target_link_libraries(test-calc PRIVATE unity m)

add_executable(test-engine tests/engine.c)
target_include_directories(test-engine PRIVATE include/engine)
target_link_libraries(test-engine PRIVATE unity SDL2)

include(CTest)
add_test(NAME calc COMMAND test-calc)
add_test(NAME engine COMMAND test-engine)
