#! /bin/bash

#
# NOTICE: System Install and System Uninstall adds or removes core libs from your OS
#

echo ""
echo "Installing System Shared Libraries"
echo "------------------------------------"
echo ""
sudo apt install -y libglfw3
sudo apt install -y libglfw3-dev
sudo apt install -y libglm
sudo apt install -y libglm-dev
sudo apt install -y libfreetype
sudo apt install -y libfreetype6
sudo apt install -y freeglut3
sudo apt install -y freeglut3-dev
sudo apt install -y libsdl1.2-dev
sudo apt install -y libsdl-image1.2-dev

# TruType fonts too