cmake_minimum_required(VERSION 3.20)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Glad ---
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# --- GLFW (binaires précompilés) ---
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/glfw/lib/libglfw3.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/glfw/include
)

# --- Frameworks macOS requis par GLFW ---
find_library(COCOA_LIBRARY Cocoa)
find_library(IOKIT_LIBRARY IOKit)
find_library(OPENGL_LIBRARY OpenGL)
find_library(COREVIDEO_LIBRARY CoreVideo)

# --- Exécutable principal ---
add_executable(OpenGL main.cpp)

target_link_libraries(OpenGL
        glad
        glfw
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)