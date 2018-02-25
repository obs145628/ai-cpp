 cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")

set(CXX_BASE_FLAGS "-g3 -Wall -Wextra -Werror -std=c++17")
#set(CXX_BASE_FLAGS "-Wall -Wextra -Werror -std=c++17 -O3 -DNDEBUG")

include_directories(include/ai)

add_subdirectory(src/bim)
add_subdirectory(src/dnn)
add_subdirectory(src/datasets)
add_subdirectory(src/graph)
add_subdirectory(src/graphics)
add_subdirectory(src/io)
add_subdirectory(src/json)
add_subdirectory(src/la)
add_subdirectory(src/logic)
#add_subdirectory(src/math) Old matrix code, TODO: merge with la
add_subdirectory(src/misc)
add_subdirectory(src/shell)
add_subdirectory(src/test)

set(SRC
  $<TARGET_OBJECTS:bim_obj>
  $<TARGET_OBJECTS:dnn_obj>
  $<TARGET_OBJECTS:datasets_obj>
  $<TARGET_OBJECTS:graph_obj>
  $<TARGET_OBJECTS:graphics_obj>
  $<TARGET_OBJECTS:io_obj>
  $<TARGET_OBJECTS:json_obj>
  $<TARGET_OBJECTS:la_obj>
  $<TARGET_OBJECTS:logic_obj>
  #$<TARGET_OBJECTS:math_obj>
  $<TARGET_OBJECTS:misc_obj>
  $<TARGET_OBJECTS:shell_obj>
  $<TARGET_OBJECTS:test_obj>
)

add_library(ai-cpp SHARED ${SRC})

add_subdirectory(examples)
add_subdirectory(tests)

install(TARGETS ai-cpp
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ai DESTINATION include)
