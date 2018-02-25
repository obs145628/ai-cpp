set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  dir.cc
  file.cc
  filesystem.cc
  path.cc
)

add_library(io_obj OBJECT ${SRC})
