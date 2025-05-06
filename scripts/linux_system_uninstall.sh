#!/bin/bash

#
# NOTICE: System Install and System Uninstall adds or removes core libs from your OS
#

echo ""
echo "Removing System Shared Libraries"
echo "------------------------------------"
echo ""
sudo apt remove -y libglfw3
sudo apt remove -y libglfw3-dev
sudo apt remove -y libglm
sudo apt remove -y libglm-dev
sudo apt remove -y libfreetype
sudo apt remove -y libfreetype6
sudo apt remove -y freeglut3
sudo apt remove -y freeglut3-dev
sudo apt remove -y libsdl1.2-dev
sudo apt remove -y libsdl-image1.2-dev

sudo rm -rf /usr/local/include/glm

echo ""
echo "Completed.."
