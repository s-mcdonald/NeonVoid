#!/bin/bash

# Set Paths
SCRIPT_DIR="$(dirname "$(realpath "$0")")"
GLM_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glm")"
GLFW_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glfw")"
FREETYPE_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/freetype")"

echo ""
echo "Removing GLM"
echo ""
cd "$GLM_DIR"
cmake --build build -- uninstall

echo " ----------- "

echo ""
echo "Removing FreeType"
echo ""
cd "$FREETYPE_DIR"
rm -rf "$FREETYPE_DIR/build"/*