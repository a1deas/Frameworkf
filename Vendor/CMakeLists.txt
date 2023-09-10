#Подключаем glfw
add_subdirectory(glfw)

#Подключаем spdlog
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE spdlog/include)

#Подключаем glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)
