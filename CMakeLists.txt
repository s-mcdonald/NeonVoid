#
# >> cmake -G "Visual Studio 17 2022" ..
#


#
# 3.2 is the min for the VS targets
#
cmake_minimum_required(VERSION 3.20)



#
# Configurable Options
#
set(PROJECT_NAME NeonVoid)
set(NeonReleaseMode "Debug")                        # Release | Debug | (Dist not supported)
set(NeonCppVersion 20)                              # 17 | 20 | 23
set(NeonBackendSystem "OpenGL")                     # OpenGL | Vulkan | DirectX | -- (Vulkan not yet supported)
set(NeonBuildDir "${CMAKE_BINARY_DIR}/build")       # Parent Output dir for build




# Project name
project("NeonVoid")

# Packaged Version
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_LEVEL 9)

# Set C++ standard
set(CMAKE_CXX_STANDARD ${NeonCppVersion})
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#
# Build Mode/Configurations & Compiler
#
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)
if(WIN32)
    set(CMAKE_CXX_COMPILER "cl.exe")
elseif(UNIX)
    set(CMAKE_BUILD_TYPE ${NeonReleaseMode})
    set(CMAKE_CXX_COMPILER "g++")
    set(OpenGL_GL_PREFERENCE GLVND) # LEGACY GLVND -- modern or old OPENGL, this is only for unix/linux
else()
    message(FATAL_ERROR "Invalid platform detected")
endif()


#
# What are we building, Vulkan, OGL or DirectX
#
if(NeonBackendSystem STREQUAL "OpenGL")
    set(NEON_BACKEND_GPU_LIB NEON_BUILD_OPENGL)
elseif(NeonBackendSystem STREQUAL "Vulkan")
    set(NEON_BACKEND_GPU_LIB NEON_BUILD_VULKAN)
endif()






#
# Game - Create the main game executable
#
set(GAME_SRC
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
add_library(GameEngine  STATIC ${GAME_ENGINE_SRC})
add_library(NeonRuntime STATIC ${NEON_RUNTIME_SRC})

#
# Set the output name of the GameEngine static library (optional)
#
set_target_properties(NeonVoid      PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${NeonBuildDir} OUTPUT_NAME "NeonVoid")
set_target_properties(GameEngine    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${NeonBuildDir} OUTPUT_NAME "GameEngine")
set_target_properties(NeonRuntime   PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${NeonBuildDir} OUTPUT_NAME "NeonRuntime")


find_package(OpenGL REQUIRED)
add_library(GLAD STATIC ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glad/glad.c)
target_include_directories(GLAD PUBLIC ${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glad)



# Freetype (Hard Paths)
set(GLM_INCLUDE_DIR         "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glm")
set(FREETYPE_INCLUDE_DIR
	"${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/include" 
	"${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/include/freetype2" 
	"${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/include"
	"${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/include/freetype"
	"${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/include/freetype2"
	"${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/include/freetype2"
)


if(WIN32)
	set(GLM_LIBRARY_DIR_W         "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glm/build/bin")
	set(GLFW_INCLUDE_DIR_W      "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/lib/include")
	set(GLFW_LIBRARY_DIR_W      "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/lib")
	set(FREETYPE_LIBRARY_DIR_W  "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/bin")

	set(GLM_LIBRARIES       "${GLM_LIBRARY_DIR_W}/glm.dll")
	set(GLFW_LIBRARIES      "${GLFW_LIBRARY_DIR_W}/glfw3.dll")
	set(FREETYPE_LIBRARIES  "${FREETYPE_LIBRARY_DIR_W}/freetype.dll")
elseif(UNIX)
	set(GLM_LIBRARY_DIR         "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glm/build/glm")
	set(GLFW_LIBRARY_DIR        "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/lib/bin")
	set(GLFW_INCLUDE_DIR        "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/glfw/build/include")
	set(FREETYPE_LIBRARY_DIR    "${CMAKE_SOURCE_DIR}/src/Runtime/vendor/freetype/build/lib")

	set(GLM_LIBRARIES       "${GLM_LIBRARY_DIR}/libglm.so")
	set(GLFW_LIBRARIES      "${GLFW_LIBRARY_DIR}/libglfw.so")
	set(FREETYPE_LIBRARIES  "${FREETYPE_LIBRARY_DIR}/libfreetype.so")
endif()



if(WIN32)
	# Includes..
	target_include_directories(NeonVoid     PRIVATE ${CMAKE_SOURCE_DIR}/src/Game/include)
	target_include_directories(GameEngine   PUBLIC ${FREETYPE_INCLUDE_DIR} ${GLFW_INCLUDE_DIR_W} ${GLM_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/src/GameEngine/vendor")
	target_include_directories(NeonRuntime  PUBLIC ${FREETYPE_INCLUDE_DIR} ${GLFW_INCLUDE_DIR_W} ${GLM_INCLUDE_DIR} )
elseif(UNIX)
	# Includes..
	target_include_directories(NeonVoid     PRIVATE ${CMAKE_SOURCE_DIR}/src/Game/include)
	target_include_directories(GameEngine   PUBLIC ${FREETYPE_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/src/GameEngine/vendor")
	target_include_directories(NeonRuntime  PUBLIC ${FREETYPE_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
endif()



# Linking..
target_link_libraries(NeonVoid          PRIVATE GameEngine NeonRuntime)
target_link_libraries(GameEngine        PRIVATE ${FREETYPE_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES} OpenGL::GL GLAD)
target_link_libraries(NeonRuntime       PRIVATE ${FREETYPE_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES} OpenGL::GL GLAD)



# GameEngine
target_include_directories(
        GameEngine PUBLIC
        ${CMAKE_SOURCE_DIR}/src/GameEngine/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor
        ${CMAKE_SOURCE_DIR}/src/Runtime/include
)
# NeonRuntime
target_include_directories(
        NeonRuntime PUBLIC
        ${CMAKE_SOURCE_DIR}/src/GameEngine/vendor
        ${CMAKE_SOURCE_DIR}/src/GameEngine/include
        ${CMAKE_SOURCE_DIR}/src/Runtime/vendor
        ${CMAKE_SOURCE_DIR}/src/Runtime/include
)


#
# Enable compiler warnings for GameEngine
#
if(WIN32)
    target_compile_options(GameEngine PRIVATE /W4 /permissive- /WX)
    target_compile_options(NeonRuntime PRIVATE /W4 /permissive- /WX)
elseif(UNIX)
    target_compile_options(GameEngine   PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(NeonRuntime  PRIVATE -Wall -Wextra -Wpedantic)
    #if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #    target_link_options(NeonRuntime     PRIVATE -fsanitize=address)
    #    target_compile_options(NeonRuntime  PRIVATE -fsanitize=address -g)
    #endif()
endif()


#
# Debug Preprocessor values
#
# Available flags/options
#  - NEON_DEBUG
#  - NEON_DEBUG_KB_INPUT
#  - NEON_DEBUG_AUDIO
#  - NEON_DEBUG_VERBOSE
#  - ${NEON_BACKEND_GPU_LIB}
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(NeonVoid     PRIVATE ${NEON_BACKEND_GPU_LIB})
    target_compile_definitions(GameEngine   PRIVATE ${NEON_BACKEND_GPU_LIB})
    target_compile_definitions(NeonRuntime  PRIVATE ${NEON_BACKEND_GPU_LIB})
else()
    target_compile_definitions(NeonVoid     PRIVATE NEON_DEBUG NEON_DEBUG_KB_INPUT ${NEON_BACKEND_GPU_LIB})
    target_compile_definitions(GameEngine   PRIVATE NEON_DEBUG NEON_DEBUG_KB_INPUT ${NEON_BACKEND_GPU_LIB})
    target_compile_definitions(NeonRuntime  PRIVATE NEON_DEBUG NEON_DEBUG_KB_INPUT ${NEON_BACKEND_GPU_LIB})
endif()




#
# Copy files on post build action
#
add_custom_command(TARGET NeonVoid POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Game/assets
        ${CMAKE_BINARY_DIR}/build/assets
        COMMAND ${CMAKE_COMMAND} -E echo "✅ Build completed and assets copied!"
        COMMENT "Copying assets to output directory"
)
