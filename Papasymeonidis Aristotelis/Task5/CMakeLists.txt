cmake_minimum_required(VERSION 3.22.1)
project(Task5)

set(CMAKE_CXX_STANDARD 20)

# Добавляем путь к директориям с заголовочными файлами
include_directories(include)

# Добавляем исходные файлы вашей библиотеки
add_library(din_arr include/din_arr/din_arr.hpp src/din_arr.cpp)
add_library(linked_list include/linked_list/linked_list.hpp src/linked_list.cpp)
add_library(stack_overflow include/stack_overflow/stack_overflow.hpp)

# Добавляем исполняемый файл
add_executable(Task5 main.cpp
        include/queue/queue.hpp
        include/double_linked_list/double_linked_list.hpp
        include/stack_overflow/stack_overflow.hpp)

# Линкуем исполняемый файл с вашими библиотеками
target_link_libraries(Task5 PRIVATE linked_list)
target_link_libraries(Task5 PRIVATE din_arr)

