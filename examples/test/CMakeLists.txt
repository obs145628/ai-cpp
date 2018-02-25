set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS}")

set(SRC
  main.cc
)

set (BIN test.out)


add_executable(${BIN} EXCLUDE_FROM_ALL ${SRC})
add_dependencies(${BIN} ai-cpp)
target_link_libraries(${BIN} ai-cpp)


add_custom_target(run_test
  COMMAND ./${BIN}
)
add_dependencies(run_test ${BIN})
