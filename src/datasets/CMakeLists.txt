set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  mnist.cc
  norm4.cc
)

add_library(datasets_obj OBJECT ${SRC})
