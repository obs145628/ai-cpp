set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  dot-tree.cc
)

add_library(graph_obj OBJECT ${SRC})
