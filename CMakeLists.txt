#
# Minimum CMake version (required)
#
cmake_minimum_required(VERSION 3.30)


#
# Configurable Options
#
set(PROJECT_NAME NeonVoid)
set(NeonReleaseMode Debug)      # Release | Debug | (Dist not supported)
set(NeonCppVersion 20)          # 20 | 23 
set(NeonBackendSystem OpenGL)   # OpenGL | (Vulkan not yet supported)


#
# Warning, dont change below here
#

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)


#
# Project name
#
project("NeonVoid")

#
# Nice .
#
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

# Build Mode
set(CMAKE_BUILD_TYPE ${NeonReleaseMode})

# Specify the compiler (g++/c++)
if(WIN32)
	set(CMAKE_CXX_COMPILER "cl.exe")
elseif(UNIX)
	set(CMAKE_CXX_COMPILER "g++")
endif()

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
    
    # AssetManager
    src/GameEngine/src/Runtime/AssetManager/AssetManager.cpp

    # Scene(s)
    src/GameEngine/src/Runtime/Scene/Scene.cpp

    # Entity
    src/GameEngine/src/Runtime/Entity/Entity.hpp
    src/GameEngine/src/Runtime/Entity/Entity.cpp
    src/GameEngine/src/Runtime/ComponentManager.cpp
    
    # Audio
    src/GameEngine/src/Runtime/Audio/Volume.hpp
    src/GameEngine/src/Runtime/Audio/AudioSystem.hpp
    src/GameEngine/src/Runtime/Audio/AudioSystem.cpp

    # Components
    src/GameEngine/src/Runtime/Components/Component.cpp
    src/GameEngine/src/Runtime/Components/QuadComponent.cpp
    src/GameEngine/src/Runtime/Components/AudioComponent.cpp
    src/GameEngine/src/Runtime/Components/TextComponent.cpp

    src/GameEngine/src/Runtime/Runtime.hpp
    src/GameEngine/src/Runtime/GameEngine.cpp
    src/GameEngine/src/Runtime/Core/Backends/OpenGL/OpenGL.cpp
    src/GameEngine/src/Runtime/Core/Backends/OpenGL/GameEngineApi.cpp
    src/GameEngine/src/Runtime/Core/Backends/OpenGL/OpenGLRenderer.cpp
    
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
)

# removed inc dirs
# ${GLEW_INCLUDE_DIR}
# ${GLEW_INCLUDE_DIRS}


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
    src/Game/src/Scenes.cpp
    src/Game/src/Scenes.hpp
)

# Create the game executable
if(WIN32)
	add_executable(NeonVoid WIN32 ${GAME_SRC})
elseif(UNIX)
	add_executable(NeonVoid ${GAME_SRC})
endif()


# Link GameEngine to the game executable
target_link_libraries(NeonVoid PRIVATE GameEngine)

# Specify include directories for the Game (can be expanded)
target_include_directories(NeonVoid PRIVATE 
    ${CMAKE_SOURCE_DIR}/Game/include
)



if(NeonBackendSystem STREQUAL "OpenGL")        
    set(NEON_BACKEND_GPU_LIB NEON_BUILD_OPENGL)
endif()

if(NeonBackendSystem STREQUAL "Vulkan")        
    set(NEON_BACKEND_GPU_LIB NEON_BUILD_VULKAN)
endif()

# Debug Preprocessor values
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(
        NeonVoid PRIVATE 
        NEON_DEBUG
        NEON_DEBUG_VERBOSE
        NEON_DEBUG_AUDIO
        ${NEON_BACKEND_GPU_LIB}
    )

    target_compile_definitions(
        GameEngine PRIVATE 
        NEON_DEBUG
        NEON_DEBUG_VERBOSE
        NEON_DEBUG_AUDIO
        ${NEON_BACKEND_GPU_LIB}
    )
else()
    target_compile_definitions(
        NeonVoid PRIVATE 
        ${NEON_BACKEND_GPU_LIB}
    )

    target_compile_definitions(
        GameEngine PRIVATE 
        ${NEON_BACKEND_GPU_LIB}
    )
endif()


#
# Specify the output directory for the executable
#
set_target_properties(NeonVoid PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)
