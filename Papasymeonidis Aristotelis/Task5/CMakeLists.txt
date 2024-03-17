cmake_minimum_required(VERSION 3.28)
project(Task5)

set(CMAKE_CXX_STANDARD 20)

# Добавляем путь к директориям с заголовочными файлами
include_directories(include)

# Добавляем исходные файлы вашей библиотеки
add_library(din_arr include/din_arr/din_arr.hpp src/din_arr.cpp)
add_library(linked_list include/linked_list/linked_list.hpp src/linked_list.cpp)

# Добавляем исполняемый файл
add_executable(Task5 main.cpp)

# Линкуем исполняемый файл с вашими библиотеками
target_link_libraries(Task5 PRIVATE din_arr)
target_link_libraries(Task5 PRIVATE linked_list)
