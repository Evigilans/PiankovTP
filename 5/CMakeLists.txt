cmake_minimum_required(VERSION 3.7)
project(TP5)

link_libraries(sqlite3)
add_compile_options(-lsqlite3)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c admin.h)
add_executable(TP5 ${SOURCE_FILES})