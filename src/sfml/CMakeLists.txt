set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  sf-app.cc
  sf-window.cc
)

add_library(sfml_obj OBJECT ${SRC})
