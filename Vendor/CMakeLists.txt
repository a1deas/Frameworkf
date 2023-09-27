#Подключаем glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(glfw)

#Подключаем spdlog
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE spdlog/include)

#Подключаем glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)

#Подключаем glad
add_subdirectory(glad)