file(GLOB_RECURSE PROJECT_FILES **.glsl)
add_custom_target(Shaders SOURCES ${PROJECT_FILES})

set_target_properties(Shaders PROPERTIES FOLDER Main)