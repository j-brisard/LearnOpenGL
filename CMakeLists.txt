cmake_minimum_required(VERSION 3.20)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/lib)

# --- Frameworks macOS requis par GLFW ---
find_library(COCOA_LIBRARY Cocoa)
find_library(IOKIT_LIBRARY IOKit)
find_library(OPENGL_LIBRARY OpenGL)
find_library(COREVIDEO_LIBRARY CoreVideo)

# --- Cible glad (compile le .c en librairie statique) ---
add_library(glad STATIC external/lib/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/include)

add_executable(HelloTriangle
        src/HelloTriangle/main.cpp
)
target_link_libraries(HelloTriangle
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Shaders
        src/Shaders/main.cpp
)
target_link_libraries(Shaders
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Textures
        src/Textures/main.cpp
        external/include/stb_image/stb_image_impl.cpp
)
target_link_libraries(Textures
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Transformations
        src/Transformations/main.cpp
        external/include/stb_image/stb_image_impl.cpp
)
target_link_libraries(Transformations
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Coordinate-Systems
        src/Coordinate-Systems/main.cpp
        external/include/stb_image/stb_image_impl.cpp
)
target_link_libraries(Coordinate-Systems
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)