add_library(glfw3webgpu STATIC glfw3webgpu.cpp)
target_include_directories(glfw3webgpu PUBLIC .)
target_include_directories(glfw3webgpu PUBLIC ../)

if (APPLE)
    target_compile_options(glfw3webgpu PRIVATE -x objective-c)
    target_link_libraries(glfw3webgpu PRIVATE "-framework Cocoa" "-framework CoreVideo" "-framework IOKit" "-framework QuartzCore")
endif ()
