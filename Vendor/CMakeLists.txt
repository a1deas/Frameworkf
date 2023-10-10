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

file(GLOB imguiFiles imgui/*.h imgui/*.cpp)
add_library(imgui STATIC ${imguiFiles}
imgui/backends/imgui_impl_glfw.h imgui/backends/imgui_impl_glfw.cpp 
imgui/backends/imgui_impl_opengl3.h imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC imgui imgui/backends)
target_link_libraries(imgui PRIVATE glfw glad)