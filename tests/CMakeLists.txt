set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS}")

set(SRC
  la-types-test.cc
  main.cc
  tests-test.cc
)


add_executable(check.out EXCLUDE_FROM_ALL ${SRC})
add_dependencies(check.out ai-cpp)
target_link_libraries(check.out ai-cpp)


add_custom_target(check
  COMMAND ./check.out
)
add_dependencies(check check.out)

add_custom_target(vg_check
  COMMAND valgrind --track-fds=yes ./check.out
)
add_dependencies(vg_check check.out)
