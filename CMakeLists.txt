#
# Minimum CMake version (required)
#
cmake_minimum_required(VERSION 3.30)


#
# Configurable Options
#
set(PROJECT_NAME NeonVoid)
set(NeonReleaseMode Debug)
set(NeonCppVersion 20)


#
# Warning, dont change below here
#


#
# Project name
#
project(PROJECT_NAME)

#
# Nice .
#
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

# Build Mode
set(CMAKE_BUILD_TYPE ${NeonReleaseMode})

# Specify the compiler (g++/c++)
set(CMAKE_CXX_COMPILER "g++")

# Set C++ standard
set(CMAKE_CXX_STANDARD ${NeonCppVersion})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL Configurations
set(OpenGL_GL_PREFERENCE GLVND)


#
# Source files
#
set(GAME_ENGINE_SRC
    src/GameEngine/src/Runtime/Types.hpp
    src/GameEngine/src/Runtime/Game.cpp
    src/GameEngine/src/Runtime/GameState.cpp
    src/GameEngine/src/Runtime/Scene.cpp
    src/GameEngine/src/Runtime/Component.cpp
    src/GameEngine/src/Runtime/AudioComponent.cpp
    src/GameEngine/src/Runtime/TextComponent.cpp
    src/GameEngine/src/Runtime/Runtime.hpp
    src/GameEngine/src/Runtime/AudioSystem.cpp
    src/GameEngine/src/Runtime/GameEngine.cpp
    src/GameEngine/src/Runtime/Core/Backends/OpenGL/OpenGL.cpp
    src/GameEngine/src/Runtime/Core/Backends/OpenGL/OpenGLRenderer.cpp
    src/GameEngine/src/Runtime/Audio/Volume.hpp
)

# Create GameEngine as a static library
add_library(GameEngine STATIC ${GAME_ENGINE_SRC})

# Set the output name of the GameEngine static library (optional)
set_target_properties(GameEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
    OUTPUT_NAME "GameEngine"
)

# GameENgine include directories
target_include_directories(GameEngine PUBLIC
    ${CMAKE_SOURCE_DIR}/src/GameEngine/src
    ${CMAKE_SOURCE_DIR}/src/GameEngine/include/stb
    ${CMAKE_SOURCE_DIR}/src/GameEngine/include/glm/glm
    ${CMAKE_SOURCE_DIR}/src/GameEngine/include/miniaudio
    ${GLEW_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

# Specify libraries to link with (GL, GLU, GLUT)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

# Link OpenGL libraries
target_link_libraries(GameEngine PRIVATE OpenGL::GL glfw ${GLEW_LIBRARY} ${GLEW_LIBRARIES})

# Enable compiler warnings for GameEngine
target_compile_options(GameEngine PRIVATE -Wall -Wextra -Wpedantic)



#
# Game - Create the main game executable
#
set(GAME_SRC
    src/Game/src/GameMain.cpp
    src/Game/src/NeonFunctions.hpp
    src/Game/src/NeonFunctions.cpp
    src/Game/src/TitleScene.cpp
)

# Create the game executable
add_executable(NeonVoid ${GAME_SRC})

# Link GameEngine to the game executable
target_link_libraries(NeonVoid PRIVATE GameEngine)

# Specify include directories for the Game (can be expanded)
target_include_directories(NeonVoid PRIVATE 
    ${CMAKE_SOURCE_DIR}/Game/include
)

# Debug Preprocessor values
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(
        NeonVoid PRIVATE 
        NEON_DEBUG
        NEON_DEBUG_VERBOSE
        NEON_DEBUG_AUDIO
    )

    target_compile_definitions(
        GameEngine PRIVATE 
        NEON_DEBUG
        NEON_DEBUG_VERBOSE
        NEON_DEBUG_AUDIO
    )
else()

endif()


#
# Specify the output directory for the executable
#
set_target_properties(NeonVoid PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)
