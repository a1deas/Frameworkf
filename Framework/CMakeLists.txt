#Создаём массив с файлами проекта
#Рекурсивно проходимся по всем папкам внутри src и добавляем все файлы .cpp и .h
file(GLOB_RECURSE PROJECT_FILES src/**.h src/**.cpp)

#Создаём visual studio проект с нашими файлами
#Статическая библиотека
add_library(Frameworkf STATIC ${PROJECT_FILES})

#Распределяем файлы по фильтрам в вижуалке
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PROJECT_FILES})

#Выбираем версию С++
target_compile_features(Frameworkf PUBLIC cxx_std_20)

#Указываем всем проектам где искать хедера конкретно этой библиотеки
target_include_directories(Frameworkf PUBLIC src)

#Для организации группируем Frameworkf в "папке" Main, которая будет видна только в вижуалке
set_target_properties(Frameworkf PROPERTIES 
FOLDER Main
)

target_link_libraries(Frameworkf PUBLIC glfw glm spdlog)