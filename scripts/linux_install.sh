#!/bin/bash

# Set Paths
SCRIPT_DIR="$(dirname "$(realpath "$0")")"
GLM_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glm")"
GLFW_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glfw3")"


echo ""
echo ""
echo ""
echo ""
echo "Removing System Shared Libraries"
echo "------------------------------------"
echo ""
echo ""
echo ""
echo "Preparing GLM: OpenGL Mathematics"
echo "Link: https://github.com/g-truc/glm"
echo ""
echo ""
cd "$GLM_DIR"
cmake \
    -DGLM_BUILD_TESTS=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -B build .
cmake --build build -- all
cmake --build build -- install


echo ""
echo "GLM should be installed now."
echo ""