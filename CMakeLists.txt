#
# Minimum CMake version required
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
project(NeonVoid)

#
# Nice .
#
SET(${PROJECT_NAME}_MAJOR_VERSION 0)
SET(${PROJECT_NAME}_MINOR_VERSION 1)
SET(${PROJECT_NAME}_PATCH_LEVEL 0)


# Now set the CMake build type using the custom variable
set(CMAKE_BUILD_TYPE ${NeonReleaseMode})



#
# Specify the compiler (g++)
#
set(CMAKE_CXX_COMPILER "g++")

#
# Set C++ standard
#
set(CMAKE_CXX_STANDARD ${NeonCppVersion})
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#
# Hopefully this dictates the new version of ogl
#
set(OpenGL_GL_PREFERENCE GLVND)



# Source files
set(SOURCE_FILES

    #
    # Main entry file
    #
    src/Entry.cpp  

    src/Game/NeonFunctions.hpp
    src/Game/NeonFunctions.cpp

    #
    # Runtime Files
    #
    src/Runtime/Types.hpp
    src/Runtime/Game.cpp
    src/Runtime/GameState.cpp
    src/Runtime/Scene.cpp
    src/Runtime/Component.cpp
    src/Runtime/AudioComponent.cpp
    src/Runtime/Runtime.hpp
    src/Runtime/AudioSystem.cpp
    src/Runtime/Core/Backends/OpenGL.cpp
    src/Runtime/GameEngine.cpp
)

#
# Create the executable (instead of a static library)
#
add_executable(NeonVoid ${SOURCE_FILES})


#
# Specify libraries to link with (GL, GLU, GLUT)
#
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

#
# Specify include directories
#
#include_directories(src)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include/stb
    ${CMAKE_SOURCE_DIR}/include/glm/glm
    ${CMAKE_SOURCE_DIR}/include/miniaudio
    ${GLEW_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)


#
# Link OpenGL libraries
#
target_link_libraries(NeonVoid PRIVATE OpenGL::GL glfw ${GLEW_LIBRARY} ${GLEW_LIBRARIES})

target_compile_options(NeonVoid PRIVATE -Wall -Wextra -Wpedantic)

#
# Debug Preprocessor values
#
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(
        NeonVoid PRIVATE 
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
