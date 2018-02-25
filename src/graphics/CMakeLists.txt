set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  color.cc
  gui-lib.cc
)

add_library(graphics_obj OBJECT ${SRC})
