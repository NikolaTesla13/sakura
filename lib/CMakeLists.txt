add_library(lib INTERFACE)

# glfw
add_subdirectory(glfw)
include_directories(glfw/include)

# Link the master library with the other libraries
target_link_libraries(lib INTERFACE glfw)
