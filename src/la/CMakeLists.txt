set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  mat_dec.cc
  matrix.cc
  random.cc
  real-chunk.cc
  tensor.cc
  vector.cc
)

add_library(la_obj OBJECT ${SRC})
