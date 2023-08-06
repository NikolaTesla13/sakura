cmake_minimum_required(VERSION 3.23)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

add_library(lib INTERFACE webgpu/webgpu.cpp)

# glfw
add_subdirectory(glfw)
include_directories(glfw/include)

# webgpu
FetchContent_Declare(
        webgpu-backend-dawn
        GIT_REPOSITORY https://github.com/eliemichel/WebGPU-distribution
        GIT_TAG        dawn
        GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(webgpu-backend-dawn)

# Link the master library with the other libraries
target_link_libraries(lib INTERFACE glfw webgpu)
