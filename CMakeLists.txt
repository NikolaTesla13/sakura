cmake_minimum_required(VERSION 3.23)
project(sakura)

add_executable(sakura src/main.cpp)

set_target_properties(sakura PROPERTIES CXX_STANDARD 23 COMPILE_WARNING_AS_ERROR ON)

add_subdirectory(lib)
target_link_libraries(sakura lib)

include_directories(src)
