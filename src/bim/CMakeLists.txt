set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  canvas.cc
  color.cc
  drawer.cc
  img.cc
)

add_library(bim_obj OBJECT ${SRC})
