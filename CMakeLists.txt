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
        src/GettingStarted/HelloTriangle/main.cpp
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
        src/GettingStarted/Shaders/main.cpp
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
        src/GettingStarted/Textures/main.cpp
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
        src/GettingStarted/Transformations/main.cpp
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
        src/GettingStarted/Coordinate-Systems/main.cpp
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

add_executable(Camera
        src/GettingStarted/Camera/main.cpp
        external/include/stb_image/stb_image_impl.cpp
)
target_link_libraries(Camera
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Colors
        src/Lighting/Colors/main.cpp
)
target_link_libraries(Colors
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Basic-Lighting
        src/Lighting/Basic-Lighting/main.cpp
)
target_link_libraries(Basic-Lighting
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Materials
        src/Lighting/Materials/main.cpp
)
target_link_libraries(Materials
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Lighting-Maps
        src/Lighting/Lighting-Maps/main.cpp
        external/include/stb_image/stb_image_impl.cpp
)
target_link_libraries(Lighting-Maps
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Light-Casters
        src/Lighting/Light-Casters/main.cpp
        external/include/stb_image/stb_image_impl.cpp
)
target_link_libraries(Light-Casters
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)

add_executable(Multiple-Lights
        src/Lighting/Multiple-Lights/main.cpp
        external/include/stb_image/stb_image_impl.cpp
)
target_link_libraries(Multiple-Lights
        glad
        glfw3
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
        ${COREVIDEO_LIBRARY}
)