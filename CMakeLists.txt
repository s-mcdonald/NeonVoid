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
        src/GameEngine/src/All.hpp

        src/GameEngine/src/Types.hpp
        src/GameEngine/src/Application.hpp
        src/GameEngine/src/Application.cpp

        # Loaders
        src/GameEngine/src/Loaders/YamlReader.hpp
        src/GameEngine/src/Loaders/YamlReader.cpp

        # AssetManager
        src/GameEngine/src/AssetManager/AssetManager.hpp
        src/GameEngine/src/AssetManager/AssetManager.cpp

        # Scene(s)
        src/GameEngine/src/Scene/Scene.hpp
        src/GameEngine/src/Scene/Scene.cpp

        # Entity
        src/GameEngine/src/Entity/Entity.hpp
        src/GameEngine/src/Entity/Entity.cpp

        # Transition
        src/GameEngine/src/Transition/Transition.hpp
        src/GameEngine/src/Transition/Transition.cpp

        # Audio
        src/GameEngine/src/Audio/Volume.hpp
        src/GameEngine/src/Audio/AudioSystem.hpp
        src/GameEngine/src/Audio/AudioSystem.cpp

        # Components
        src/GameEngine/src/Components/ShaderComponent.cpp
        src/GameEngine/src/Components/AudioComponent.cpp
        src/GameEngine/src/Components/TextComponent.cpp
        src/GameEngine/src/Components/PositionComponent.cpp
        src/GameEngine/src/Components/MovementComponent.cpp

        # Engine Abstracts

        src/GameEngine/src/RuntimeBridge.hpp
        src/GameEngine/src/RuntimeBridge.cpp

        # Platform
        src/Runtime/src/IntRuntime.hpp
        src/Runtime/src/ExtRuntime.hpp
        src/Runtime/src/RuntimeApi.hpp
        src/Runtime/src/RuntimeApi.cpp

        src/Runtime/src/Factory/ShaderFactory.hpp
        src/Runtime/src/Factory/ShaderFactory.cpp

        src/Runtime/src/Backends/IInput.hpp
        src/Runtime/src/Backends/IWindow.hpp
        src/Runtime/src/Backends/IWindow.hpp
        src/Runtime/src/Backends/IShader.hpp
        src/Runtime/src/Backends/IPlatform.hpp
        src/Runtime/src/Backends/IRenderer.hpp
        src/Runtime/src/Backends/IFrameBuffer.hpp
        src/Runtime/src/Backends/IVertexArray.hpp
        src/Runtime/src/Backends/IVertexBuffer.hpp


        src/Runtime/src/Backends/OpenGL/OpenGLHeaders.hpp
        src/Runtime/src/Backends/OpenGL/OpenGL.hpp
        src/Runtime/src/Backends/OpenGL/OpenGL.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLInput.hpp
        src/Runtime/src/Backends/OpenGL/OpenGLInput.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLShader.hpp
        src/Runtime/src/Backends/OpenGL/OpenGLShader.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLRenderer.hpp
        src/Runtime/src/Backends/OpenGL/OpenGLRenderer.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLVertexArray.hpp
        src/Runtime/src/Backends/OpenGL/OpenGLVertexArray.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLVertexBuffer.hpp
        src/Runtime/src/Backends/OpenGL/OpenGLVertexBuffer.cpp
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
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/GameEngine/src
        ${CMAKE_SOURCE_DIR}/src/GameEngine/vendor
        ${CMAKE_SOURCE_DIR}/src/GameEngine/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/src
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor
        ${CMAKE_SOURCE_DIR}/src/Runtime/include
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
        src/Game/src/Mankind.hpp
        src/Game/src/GameMain.cpp # Entry
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
