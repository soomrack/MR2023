cmake_minimum_required(VERSION 2.8)

# Название проекта
project(OrangeBot_bot)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Подключаем OpenCV
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${CMAKE_SOURCE_DIR}/../OrangeBot)

# Указываем список исходных файлов
set(SOURCES
    ${CMAKE_SOURCE_DIR}/../OrangeBot/orange_bot.cpp
    ${CMAKE_SOURCE_DIR}/../OrangeBot/orange_bot_camera.cpp
    ${CMAKE_SOURCE_DIR}/../OrangeBot/orange_bot_keydetect.cpp
    ${CMAKE_SOURCE_DIR}/../OrangeBot/orange_bot_uart.cpp
    ${CMAKE_SOURCE_DIR}/../OrangeBot/orange_bot_udp_client.cpp
    ${CMAKE_SOURCE_DIR}/../OrangeBot/orange_bot_udp_server.cpp
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Линкуем OpenCV библиотеки и потоки
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
