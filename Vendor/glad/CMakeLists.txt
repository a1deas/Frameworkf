set (PROJECT_FILES include/glad/glad.h include/KHR/khrplatform.h src/glad.c)

add_library(glad STATIC ${PROJECT_FILES})

target_include_directories(glad PUBLIC include)

set_target_properties(glad PROPERTIES FOLDER Vendor)