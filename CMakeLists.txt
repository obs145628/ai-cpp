cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CXX_BASE_FLAGS "-g3 -Wall -Wextra -Werror -std=c++17")
#set(CXX_BASE_FLAGS "-Wall -Wextra -Werror -std=c++17 -O3 -DNDEBUG")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})


include_directories(include/ai)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
