#
# Minimum CMake version (required)
# For VS 2022, min ver should 3.2
# bata fie: cmake -G "Visual Studio 17 2022" ..
#
cmake_minimum_required(VERSION 3.20)


#
# Configurable Options
#
set(PROJECT_NAME NeonVoid)
set(NeonReleaseMode Debug)      # Release | Debug | (Dist not supported)
set(NeonCppVersion 20)          # 20 | 23 
set(NeonBackendSystem OpenGL)   # OpenGL | (Vulkan not yet supported)



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


#
# Build Mode/Configurations
#
set("Debug;Release" CACHE STRING "Configurations" FORCE)
if(UNIX)
    set(CMAKE_BUILD_TYPE ${NeonReleaseMode})
endif()



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
        # includes
        src/Game/include/GameScripts.hpp

        # src
        src/Game/src/MyGame.hpp
        src/Game/src/EntryMain.cpp
        src/Game/src/Scripts/EntityScript.cpp
        src/Game/src/Scripts/SceneScript.cpp
)

#
# Game Engine Source files
#
set(GAME_ENGINE_SRC
        # Includes
        src/GameEngine/include/NeonEngine/YamlReader.hpp
        src/GameEngine/include/NeonEngine/ScriptRegistry.hpp
        src/GameEngine/include/NeonEngine/ComponentLoader.hpp
        src/GameEngine/include/NeonEngine/AssetManager.hpp
        src/GameEngine/include/NeonEngine/Types.hpp
        src/GameEngine/include/NeonEngine/PhysixSystem.hpp
        src/GameEngine/include/NeonEngine/Application.hpp
        src/GameEngine/include/NeonEngine/All.hpp
        src/GameEngine/include/NeonEngine/Scene.hpp
        src/GameEngine/include/NeonEngine/Entity.hpp
        src/GameEngine/include/NeonEngine/Volume.hpp
        src/GameEngine/include/NeonEngine/AudioSystem.hpp
        src/GameEngine/include/NeonEngine/RuntimeBridge.hpp
        src/GameEngine/include/NeonEngine/Components.hpp
        src/GameEngine/include/NeonEngine/SceneTypeConverter.hpp
        src/GameEngine/include/NeonEngine/EntityTypeConverter.hpp
        src/GameEngine/include/NeonEngine/YamlSceneAsserter.hpp
        src/GameEngine/include/NeonEngine/CollisionSystem.hpp

        # App
        src/GameEngine/src/Application.cpp

        # Loaders
        src/GameEngine/src/Assets/Loaders/ComponentLoader.cpp
        src/GameEngine/src/Assets/AssetManager.cpp

        # Systems
        src/GameEngine/src/Systems/PhysixSystem.cpp
        src/GameEngine/src/Systems/CollisionSystem.cpp

        # Scene
        src/GameEngine/src/Scene/Scene.cpp
        src/GameEngine/src/Scene/Entity.cpp

        # Audio
        src/GameEngine/src/Audio/AudioSystem.cpp

        # Components
        src/GameEngine/src/Components/ShaderComponent.cpp
        src/GameEngine/src/Components/AudioComponent.cpp
        src/GameEngine/src/Components/TextComponent.cpp
        src/GameEngine/src/Components/MovementComponent.cpp

        # Utils
        src/GameEngine/src/Utils/EntityTypeConverter.cpp
        src/GameEngine/src/Utils/SceneTypeConverter.cpp

        # Serialization
        src/GameEngine/src/Serialization/YamlReader.cpp
        src/GameEngine/src/Serialization/YamlSceneAsserter.cpp

        # Engine Abstracts
        src/GameEngine/src/RuntimeBridge.cpp
)

#
# NeonRuntime Source files
#
set(NEON_RUNTIME_SRC
        # Includes
        src/Runtime/include/NeonRuntime/RTTypes.hpp
        src/Runtime/include/NeonRuntime/IntRuntime.hpp
        src/Runtime/include/NeonRuntime/ExtRuntime.hpp
        src/Runtime/include/NeonRuntime/RuntimeApi.hpp
        src/Runtime/include/NeonRuntime/PlatformFactory.hpp
        src/Runtime/include/NeonRuntime/IInput.hpp
        src/Runtime/include/NeonRuntime/IWindow.hpp
        src/Runtime/include/NeonRuntime/IShader.hpp
        src/Runtime/include/NeonRuntime/IPlatform.hpp
        src/Runtime/include/NeonRuntime/IRenderer.hpp
        src/Runtime/include/NeonRuntime/IVertexBuffer.hpp
        src/Runtime/include/NeonRuntime/ITextBuffer.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLHeaders.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGL.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLInput.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLShader.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLRenderer.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLVertexBuffer.hpp
        src/Runtime/include/NeonRuntime/Backends/OpenGLTextBuffer.hpp

        # Platform
        src/Runtime/src/RuntimeApi.cpp
        src/Runtime/src/Factory/PlatformFactory.cpp
        src/Runtime/src/Backends/OpenGL/OpenGL.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLInput.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLShader.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLRenderer.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLVertexBuffer.cpp
        src/Runtime/src/Backends/OpenGL/OpenGLTextBuffer.cpp

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
#        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/include
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
#        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/include
)

# Include dir for Main Game
target_include_directories(NeonVoid PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Game/include
)


# Specify libraries to link with (GL, GLU, GLUT)
#find_package(OpenGL REQUIRED)
#find_package(glfw3 REQUIRED)
#find_package(glm CONFIG REQUIRED)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

# Define the executable project
if(WIN32)
    message(FATAL_ERROR "Lib Paths have not been setup for windows")
elseif(UNIX)
    # Freetype (Hard Paths)
    set(FREETYPE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/include")
    set(FREETYPE_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/lib")
    set(FREETYPE_LIBRARIES "${FREETYPE_LIBRARY_DIR}/libfreetype.so")

    # GLFW (Hard Paths)
    set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/include")
    set(GLFW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/lib")
    set(GLFW_LIBRARIES "${GLFW_LIBRARY_DIR}/libglfw.so")
endif()


# includes
target_include_directories(GameEngine  PUBLIC ${FREETYPE_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR})
target_include_directories(NeonRuntime PUBLIC ${FREETYPE_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR})

# Linking ..
target_link_libraries(NeonVoid PRIVATE GameEngine NeonRuntime)
target_link_libraries(GameEngine  PRIVATE ${FREETYPE_LIBRARIES} ${GLFW_LIBRARIES} OpenGL::GL)
target_link_libraries(NeonRuntime PRIVATE ${FREETYPE_LIBRARIES} ${GLFW_LIBRARIES} OpenGL::GL)

#
# Enable compiler warnings for GameEngine
#
#target_compile_options(GameEngine PRIVATE -Wall -Wextra -Wpedantic)
#target_compile_options(NeonRuntime PRIVATE -Wall -Wextra -Wpedantic)





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
# Copy files on post build action
#
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Game/assets
        ${CMAKE_BINARY_DIR}/build/assets
        COMMENT "Copying assets to build directory"
)

add_dependencies(NeonVoid copy_assets)
