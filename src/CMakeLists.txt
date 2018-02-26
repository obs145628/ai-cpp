add_subdirectory(bim)
add_subdirectory(dnn)
add_subdirectory(datasets)
add_subdirectory(graph)
add_subdirectory(graphics)
add_subdirectory(io)
add_subdirectory(json)
add_subdirectory(la)
add_subdirectory(logic)
#add_subdirectory(math) Old matrix code, TODO: merge with la
add_subdirectory(misc)
add_subdirectory(sfml)
add_subdirectory(shell)
add_subdirectory(test)


set(SRC
  $<TARGET_OBJECTS:bim_obj>
  $<TARGET_OBJECTS:dnn_obj>
  $<TARGET_OBJECTS:datasets_obj>
  $<TARGET_OBJECTS:graph_obj>
  $<TARGET_OBJECTS:graphics_obj>
  $<TARGET_OBJECTS:io_obj>
  $<TARGET_OBJECTS:json_obj>
  $<TARGET_OBJECTS:la_obj>
  $<TARGET_OBJECTS:logic_obj>
  #$<TARGET_OBJECTS:math_obj>
  $<TARGET_OBJECTS:misc_obj>
  $<TARGET_OBJECTS:sfml_obj>
  $<TARGET_OBJECTS:shell_obj>
  $<TARGET_OBJECTS:test_obj>
)

add_library(ai-cpp SHARED ${SRC})
target_link_libraries(ai-cpp ${SFML_LIBRARIES})

install(TARGETS ai-cpp
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ai DESTINATION include)
