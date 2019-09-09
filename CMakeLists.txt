cmake_minimum_required(VERSION 3.14)
project(embedded_sql)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sqlcipher)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DSQLITE_HAS_CODEC)