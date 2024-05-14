cmake_minimum_required(VERSION 3.20)
project(tank-battle)

add_executable(tankbattle "" "")
target_include_directories(tankbattle PRIVATE include)
target_sources(tankbattle PRIVATE
	src/tankbattle.c
        src/calc.c
)
target_link_libraries(tankbattle SDL2 m)

add_subdirectory(unity)
add_executable(test-suite tests/test.c src/calc.c)
target_include_directories(test-suite PRIVATE include)
target_link_libraries(test-suite PRIVATE unity)
include(CTest)
add_test(NAME test COMMAND test-suite)
