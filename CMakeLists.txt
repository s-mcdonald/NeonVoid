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

# Compiler
if(WIN32)
	set(CMAKE_CXX_COMPILER "cl.exe")
elseif(UNIX)
	set(CMAKE_CXX_COMPILER "g++")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD ${NeonCppVersion})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND)


#
# Game - Create the main game executable
#
set(GAME_SRC
        src/Game/src/Core/MyGame.hpp
        src/Game/src/EntryMain.cpp
)

#
# Game Engine Source files
#
set(GAME_ENGINE_SRC
        # Includes
        src/GameEngine/include/NeonEngine/YamlReader.hpp
        src/GameEngine/include/NeonEngine/AssetManager.hpp
        src/GameEngine/include/NeonEngine/Types.hpp
        src/GameEngine/include/NeonEngine/Application.hpp
        src/GameEngine/include/NeonEngine/All.hpp
        src/GameEngine/include/NeonEngine/Scene.hpp
        src/GameEngine/include/NeonEngine/Entity.hpp
        src/GameEngine/include/NeonEngine/Transition.hpp
        src/GameEngine/include/NeonEngine/Volume.hpp
        src/GameEngine/include/NeonEngine/AudioSystem.hpp
        src/GameEngine/include/NeonEngine/RuntimeBridge.hpp
        src/GameEngine/include/NeonEngine/Components.hpp
        src/GameEngine/include/NeonEngine/SceneTypeConverter.hpp
        src/GameEngine/include/NeonEngine/YamlSceneAsserter.hpp


        # App
        src/GameEngine/src/Application.cpp

        # Loaders
        src/GameEngine/src/Assets/Loaders/YamlReader.cpp
        src/GameEngine/src/Assets/AssetManager.cpp

        # Scene
        src/GameEngine/src/Scene/Scene.cpp
        src/GameEngine/src/Scene/Entity.cpp

        # Transition
        src/GameEngine/src/Transition/Transition.cpp

        # Audio
        src/GameEngine/src/Audio/AudioSystem.cpp

        # Components
        src/GameEngine/src/Components/ShaderComponent.cpp
        src/GameEngine/src/Components/AudioComponent.cpp
        src/GameEngine/src/Components/TextComponent.cpp
        src/GameEngine/src/Components/PositionComponent.cpp
        src/GameEngine/src/Components/MovementComponent.cpp

        # Utils
        src/GameEngine/src/Utils/SceneTypeConverter.cpp
        src/GameEngine/src/Utils/YamlSceneAsserter.cpp

        # Engine Abstracts
        src/GameEngine/src/RuntimeBridge.cpp
)

#
# NeonRuntime Source files
#
set(NEON_RUNTIME_SRC
        # Includes
        src/Runtime/include/NeonRuntime/IntRuntime.hpp
        src/Runtime/include/NeonRuntime/ExtRuntime.hpp
        src/Runtime/include/NeonRuntime/RuntimeApi.hpp
        src/Runtime/include/NeonRuntime/ShaderFactory.hpp
        src/Runtime/include/NeonRuntime/BufferFactory.hpp
        src/Runtime/include/NeonRuntime/PlatformFactory.hpp
        src/Runtime/include/NeonRuntime/IInput.hpp
        src/Runtime/include/NeonRuntime/IWindow.hpp
        src/Runtime/include/NeonRuntime/IWindow.hpp
        src/Runtime/include/NeonRuntime/IShader.hpp
        src/Runtime/include/NeonRuntime/IPlatform.hpp
        src/Runtime/include/NeonRuntime/IRenderer.hpp
        src/Runtime/include/NeonRuntime/IFrameBuffer.hpp
        src/Runtime/include/NeonRuntime/IVertexArray.hpp
        src/Runtime/include/NeonRuntime/IVertexBuffer.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLHeaders.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGL.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLInput.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLShader.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLRenderer.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLVertexBuffer.hpp

        # Platform
        src/Runtime/src/RuntimeApi.cpp
        src/Runtime/src/Factory/ShaderFactory.cpp
        src/Runtime/src/Factory/BufferFactory.cpp
        src/Runtime/src/Factory/PlatformFactory.cpp
        src/Runtime/src/Backends/OpenGL/OpenGL.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLInput.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLShader.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLRenderer.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLVertexBuffer.cpp

        # External compile
        src/Runtime/vendor/glad/glad.c
)


# Define the executable project
if(WIN32)
    add_executable(NeonVoid WIN32 ${GAME_SRC})
elseif(UNIX)
    add_executable(NeonVoid ${GAME_SRC})
endif()

#
# Define GameEngine & NeonRuntime as a static library
#
add_library(GameEngine STATIC ${GAME_ENGINE_SRC})
add_library(NeonRuntime STATIC ${NEON_RUNTIME_SRC})

#
# Set the output name of the GameEngine static library (optional)
#
set_target_properties(
        GameEngine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
        OUTPUT_NAME "GameEngine"
)
set_target_properties(
        NeonRuntime PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
        OUTPUT_NAME "NeonRuntime"
)

set_target_properties(
        NeonVoid PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
        OUTPUT_NAME "NeonVoid"
)


# GameEngine include directories
target_include_directories(
        GameEngine PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/GameEngine/src
        ${CMAKE_SOURCE_DIR}/src/GameEngine/vendor
        ${CMAKE_SOURCE_DIR}/src/GameEngine/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/src
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor
        ${CMAKE_SOURCE_DIR}/src/Runtime/include
)

# NeonRuntime include directories
target_include_directories(
        NeonRuntime PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/GameEngine/src
        ${CMAKE_SOURCE_DIR}/src/GameEngine/vendor
        ${CMAKE_SOURCE_DIR}/src/GameEngine/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/src
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor
        ${CMAKE_SOURCE_DIR}/src/Runtime/include
)

# Include dir for Main Game
target_include_directories(NeonVoid PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Game/include
)



# removed inc dirs
# ${GLEW_INCLUDE_DIR}
# ${GLEW_INCLUDE_DIRS}


# Specify libraries to link with (GL, GLU, GLUT)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)

# Link OpenGL libraries
#target_link_libraries(GameEngine PRIVATE OpenGL::GL glfw ${GLEW_LIBRARY} ${GLEW_LIBRARIES})
#target_link_libraries(GameEngine PRIVATE OpenGL::GL glfw )
target_link_libraries(NeonRuntime PRIVATE OpenGL::GL glfw )
target_include_directories(GameEngine PUBLIC ${FREETYPE_INCLUDE_DIRS})
target_include_directories(NeonRuntime PUBLIC ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(GameEngine PRIVATE ${FREETYPE_LIBRARIES})
target_link_libraries(NeonRuntime PRIVATE ${FREETYPE_LIBRARIES})


# Enable compiler warnings for GameEngine
target_compile_options(GameEngine PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(NeonRuntime PRIVATE -Wall -Wextra -Wpedantic)







# Link GameEngine to the game executable & Runtime
target_link_libraries(NeonVoid PRIVATE GameEngine NeonRuntime)




if(NeonBackendSystem STREQUAL "OpenGL")        
    set(NEON_BACKEND_GPU_LIB NEON_BUILD_OPENGL)
endif()

if(NeonBackendSystem STREQUAL "Vulkan")        
    set(NEON_BACKEND_GPU_LIB NEON_BUILD_VULKAN)
endif()


#
# Debug Preprocessor values
#
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

    target_compile_definitions(
            NeonRuntime PRIVATE
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

    target_compile_definitions(
            NeonRuntime PRIVATE
            ${NEON_BACKEND_GPU_LIB}
    )
endif()


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


#
# Specify the output directory for the executable
#
#set(BINARY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/build) # Original build directory
#set(FINAL_OUTPUT_DIR ${CMAKE_BINARY_DIR}/src/Sandbox/app) # Destination directory for final binary
#
#set_target_properties(NeonVoid PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}
#)



#
# Copy files on post build action
#
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Game/assets
        ${CMAKE_BINARY_DIR}/build/assets
        COMMENT "Copying assets to build directory"
)

add_dependencies(NeonVoid copy_assets)

