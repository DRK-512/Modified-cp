cmake_minimum_required(VERSION 3.10)
project(mod_cp)

add_executable(mod_cp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/functions.c
)
target_include_directories(mod_cp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_compile_options(mod_cp
	Wall
)
