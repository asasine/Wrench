cmake_minimum_required(VERSION 3.0.0)
project(wrench VERSION 0.0.0)
set(CMAKE_C_STANDARD 11)

add_executable(wrench src/main.c)

target_include_directories(wrench PRIVATE "${CMAKE_SOURCE_DIR}/lib/wren/src/include")
target_link_libraries(wrench "${CMAKE_SOURCE_DIR}/lib/wren/lib/libwren.a")
