cmake_minimum_required(VERSION 3.20)
project(AoC2025)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DAYS day01 day02 day03)

foreach(DAY IN LISTS DAYS)
	add_executable(${DAY} ${DAY}/main.cpp)

	set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/${DAY})

	set_target_properties(${DAY} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    )
    file(MAKE_DIRECTORY ${OUTPUT_DIR})

    add_custom_command(TARGET ${DAY} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/${DAY}/input.txt
            ${OUTPUT_DIR}/input.txt
    )
endforeach()


#add_executable(day01 Day1/main.cpp)

#configure_file(Day1/input.txt input)