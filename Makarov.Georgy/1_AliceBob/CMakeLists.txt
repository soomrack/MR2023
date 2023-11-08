cmake_minimum_required(VERSION 3.6)
project(AliceBob)

add_executable(AliceBob main.c)
target_link_libraries(AliceBob PRIVATE m)