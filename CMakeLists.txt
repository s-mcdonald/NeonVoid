#
# Minimum CMake version required
#
cmake_minimum_required(VERSION 3.10)

#
# Project name
#
project(NeonVoid)

#
# Specify the compiler (g++)
#
set(CMAKE_CXX_COMPILER "g++")

#
# Set C++ standard
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Set build type (Release or Debug)
#
set(CMAKE_BUILD_TYPE Release)

#
# Specify include directories
#
include_directories(src)

# Source files
set(SOURCE_FILES
    src/Entry.cpp   
)

#
# Create the executable (instead of a static library)
#
add_executable(neon-void ${SOURCE_FILES})

#
# Specify libraries to link with (GL, GLU, GLUT)
#
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#
# Link OpenGL libraries
#
target_link_libraries(neon-void PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT)


#
# Specify the output directory for the executable
#
set_target_properties(neon-void PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)
