cmake_minimum_required(VERSION 3.20)
#Название решения(sln)
project(Frameworkf)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

add_subdirectory(Framework)
add_subdirectory(Testbed)
add_subdirectory(Vendor)

file(COPY ${CMAKE_SOURCE_DIR}/.clang-format DESTINATION ${CMAKE_CURRENT_BINARY_DIR})