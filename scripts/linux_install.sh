#!/bin/bash

# Set Paths
SCRIPT_DIR="$(dirname "$(realpath "$0")")"
GLM_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glm")"
GLFW_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glfw3")"
FREETYPE_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/freetype")"


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
    -DBUILD_SHARED_LIBS=ON \
    -B build .
cmake --build build -- all
cmake --build build -- install


echo "Preparing FreeType"
echo "Link: https://github.com/freetype/freetype"
echo ""
echo ""
cd "$FREETYPE_DIR"
rm -rf "$FREETYPE_DIR/build"
mkdir "$FREETYPE_DIR/build"
cmake -B build -D CMAKE_INSTALL_PREFIX="$FREETYPE_DIR/build" -D BUILD_SHARED_LIBS=true -D CMAKE_BUILD_TYPE=Release "$FREETYPE_DIR"
cmake --build build --target install



echo ""
echo "GLM and FreeType should now be installed."
echo ""
