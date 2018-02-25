set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  activation.cc
  fully-connected-layer.cc
  network.cc
  sgd-optimizer.cc
)

add_library(dnn_obj OBJECT ${SRC})
