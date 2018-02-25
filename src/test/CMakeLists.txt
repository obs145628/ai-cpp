set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  test-register.cc
  test-suite.cc
)

add_library(test_obj OBJECT ${SRC})
