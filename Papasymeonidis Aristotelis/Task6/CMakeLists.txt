cmake_minimum_required(VERSION 3.22.1) # Установка минимальной требуемой версии CMake

project(Task6) # Название вашего проекта

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление исполняемого файла
# Предполагается, что весь код находится в файле main.cpp
add_executable(Task6 parsing.cpp)

# Если у вас есть другие .cpp файлы, например, flight.cpp, где реализованы методы класса Flight,
# их также нужно добавить в список исходников:
# add_executable(FlightInfo main.cpp flight.cpp)