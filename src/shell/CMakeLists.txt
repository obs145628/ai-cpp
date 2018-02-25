set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

set(SRC
  arguments.cc
  command.cc
  date.cc
  grid.cc
  ipc.cc
  shell.cc
  shell-canvas.cc
  shell-drawable.cc
  shell-scene.cc
  shell-sprite.cc
  timer.cc
)

add_library(shell_obj OBJECT ${SRC})
