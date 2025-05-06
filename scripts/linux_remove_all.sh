#!/bin/bash


echo ""
echo ""
echo ""
echo ""
echo "Removing System Shared Libraries"
echo "------------------------------------"
echo ""
echo ""
sudo apt remove -y libglfw3
sudo apt remove -y libglfw3-dev
sudo apt remove -y libglm
sudo apt remove -y libglm-dev

sudo rm -rf /usr/local/include/glm


sudo apt remove -y libfreetype
sudo apt remove -y libfreetype6

echo ""
echo "Completed.."
