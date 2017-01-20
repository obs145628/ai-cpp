cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14")

include_directories(include/ai)

add_subdirectory(src/io)
add_subdirectory(src/json)
add_subdirectory(src/math)
add_subdirectory(src/misc)
add_subdirectory(src/shell)

set(SRC
  $<TARGET_OBJECTS:io_obj>
  $<TARGET_OBJECTS:json_obj>
  $<TARGET_OBJECTS:math_obj>
  $<TARGET_OBJECTS:misc_obj>
  $<TARGET_OBJECTS:shell_obj>
)

add_library(ai-cpp SHARED ${SRC})

add_subdirectory(tests)

set(TESTS_SRC
  $<TARGET_OBJECTS:obs_tests_obj>
)


add_executable(check.out EXCLUDE_FROM_ALL ${TESTS_SRC})
add_dependencies(check.out ai-cpp)
target_link_libraries(check.out ai-cpp)


add_custom_target(check
  COMMAND ./check.out
)
add_dependencies(check check.out)

add_custom_target(vg
  COMMAND valgrind --track-fds=yes ./check.out
)
add_dependencies(vg check.out)

install(TARGETS ai-cpp
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ai DESTINATION include)
