#Создаём массив с файлами проекта
#Рекурсивно проходимся по всем папкам внутри src и добавляем все файлы .cpp и .h
file(GLOB_RECURSE PROJECT_FILES src/**.h src/**.cpp)

#Создаём exe-шник
add_executable(Testbed ${PROJECT_FILES})

#Распределяем файлы по фильтрам в вижуалке
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PROJECT_FILES})

#Выбираем версию С++
target_compile_features(Testbed PUBLIC cxx_std_20)

#Подключаем к exe-шнику библиотеку Frameworkf
target_link_libraries(Testbed PUBLIC Frameworkf)

#Указываем всем проектам где искать хедера конкретно этой библиотеки
target_include_directories(Testbed PUBLIC src)

#Для организации группируем Testbed в "папке" Main, которая будет видна только в вижуалке
set_target_properties(Testbed PROPERTIES 
FOLDER Main
VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
