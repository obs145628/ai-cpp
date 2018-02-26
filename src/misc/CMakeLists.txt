set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  parse-error.cc
  random.cc
  random-mt.cc
)

add_library(misc_obj OBJECT ${SRC})
