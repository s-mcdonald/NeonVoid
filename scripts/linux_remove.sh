#!/bin/bash

# Set Paths
SCRIPT_DIR="$(dirname "$(realpath "$0")")"
GLM_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glm")"
GLFW_DIR="$(realpath "$SCRIPT_DIR/../src/Runtime/vendor/glfw3")"

echo ""
echo "Removing GLM"
echo ""
cd "$GLM_DIR"
cmake --build build -- uninstall


