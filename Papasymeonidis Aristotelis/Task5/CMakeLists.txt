cmake_minimum_required(VERSION 3.28)
project(Task5)

set(CMAKE_CXX_STANDARD 20)

# Добавляем исходные файлы вашей библиотеки
add_library(din_arr din_arr.hpp din_arr.cpp)

# Добавляем исполняемый файл и указываем, что он использует вашу библиотеку
add_executable(Task5 main.cpp)

# Укажите директорию, содержащую ваши заголовочные файлы
include_directories(Task5)

# Линкуем ваш исполняемый файл с вашей библиотекой
target_link_libraries(Task5 PRIVATE din_arr)
