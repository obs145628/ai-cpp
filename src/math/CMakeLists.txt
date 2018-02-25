set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  cholesky.cc
  cramer.cc
  gauss.cc
  lu.cc
  matrix.cc
  qr.cc
  random.cc
  utils.cc
  vector.cc
  vlist.cc
)

add_library(math_obj OBJECT ${SRC})
