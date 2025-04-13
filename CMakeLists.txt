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
        src/GameEngine/src/Runtime/Runtime.hpp
        src/GameEngine/src/Runtime/Runtime.cpp

        src/GameEngine/src/Runtime/Types.hpp
        src/GameEngine/src/Runtime/Game.hpp
        src/GameEngine/src/Runtime/Game.cpp

        # AssetManager
        src/GameEngine/src/Runtime/AssetManager/AssetManager.hpp
        src/GameEngine/src/Runtime/AssetManager/AssetManager.cpp

        # Input Control
        src/GameEngine/src/Runtime/Input/Input.hpp

        # Scene(s)
        src/GameEngine/src/Runtime/Scene/Scene.hpp
        src/GameEngine/src/Runtime/Scene/Scene.cpp

        # Entity
        src/GameEngine/src/Runtime/Entity/Entity.hpp
        src/GameEngine/src/Runtime/Entity/Entity.cpp

        # Transition
        src/GameEngine/src/Runtime/Transition/Transition.hpp
        src/GameEngine/src/Runtime/Transition/Transition.cpp

        # Audio
        src/GameEngine/src/Runtime/Audio/Volume.hpp
        src/GameEngine/src/Runtime/Audio/AudioSystem.hpp
        src/GameEngine/src/Runtime/Audio/AudioSystem.cpp

        # Components
        src/GameEngine/src/Runtime/Components/ShaderComponent.cpp
        src/GameEngine/src/Runtime/Components/AudioComponent.cpp
        src/GameEngine/src/Runtime/Components/TextComponent.cpp
        src/GameEngine/src/Runtime/Components/PositionComponent.cpp
        src/GameEngine/src/Runtime/Components/MovementComponent.cpp

        src/GameEngine/src/Runtime/Engine/Shader.hpp
        src/GameEngine/src/Runtime/Engine/Shader.cpp
        src/GameEngine/src/Runtime/Engine/GameEngine.hpp
        src/GameEngine/src/Runtime/Engine/GameEngine.cpp
        src/GameEngine/src/Runtime/Engine/Backends/VertexBuffer.hpp

        # Platform
        src/GameEngine/src/Runtime/Engine/Backends/Container.hpp
        src/GameEngine/src/Runtime/Engine/Backends/Container.cpp
        src/GameEngine/src/Runtime/Engine/Backends/Platform.hpp
        src/GameEngine/src/Runtime/Engine/Backends/IWindow.hpp
        src/GameEngine/src/Runtime/Engine/Backends/IWindow.hpp
        src/GameEngine/src/Runtime/Engine/Backends/IRenderer.hpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGL.hpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGL.cpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLInput.hpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLInput.cpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/GameEngineApi.hpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/GameEngineApi.cpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLRenderer.hpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLRenderer.cpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLVertexBuffer.hpp
        src/GameEngine/src/Runtime/Engine/Backends/OpenGL/OpenGLVertexBuffer.cpp
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
    ${CMAKE_SOURCE_DIR}/src/GameEngine/vendor/stb
    ${CMAKE_SOURCE_DIR}/src/GameEngine/vendor/miniaudio
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

        src/Game/src/MyGame.hpp
        src/Game/src/MyGame.cpp
        src/Game/src/Mankind.hpp
        src/Game/src/GameMain.cpp # Entry
        src/Game/src/Scenes/TitleScene.cpp
        src/Game/src/Scenes/TitleScene.hpp
        src/Game/src/Scenes/GamePlayScene.cpp
        src/Game/src/Scenes/GamePlayScene.hpp
        src/Game/src/Entities/MoveablePlayerEntity.hpp
        src/Game/src/Entities/MoveablePlayerEntity.cpp
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
            #NEON_DEBUG_VERBOSE
            NEON_DEBUG_KB_INPUT
            #NEON_DEBUG_AUDIO
            ${NEON_BACKEND_GPU_LIB}
    )

    target_compile_definitions(
            GameEngine PRIVATE
            NEON_DEBUG
            #NEON_DEBUG_VERBOSE
            NEON_DEBUG_KB_INPUT
            #NEON_DEBUG_AUDIO
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


#
# Sandbox Executable
#
#set(SANDBOX_SRC
#        src/Sandbox/src/Main.cpp
#        ${CMAKE_SOURCE_DIR}/src/Sandbox/include/glad/glad.c
#)
#add_executable(NeonVoidSandbox ${SANDBOX_SRC})
#target_include_directories(NeonVoidSandbox PUBLIC
#        ${CMAKE_SOURCE_DIR}/src/Sandbox/include
#)
#target_link_libraries(NeonVoidSandbox PRIVATE OpenGL::GL)
#target_link_libraries(NeonVoidSandbox PRIVATE OpenGL::GL glfw)
#
#set_target_properties(NeonVoidSandbox PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
#)
