set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  json.cc
  json-null.cc
  json-bool.cc
  json-number.cc
  json-string.cc
  json-array.cc
  json-object.cc
)

add_library(json_obj OBJECT ${SRC})
