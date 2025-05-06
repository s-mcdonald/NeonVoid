# NeonVoid

> **Note:** This project is for educational purposes and is currently in active development.

A simple 2D GameEngine written in C++.

## About NeonVoid Engine

This project started as a personal journey to learn C++. I had been inspired by the YouTuber [The Cherno](https://github.com/thecherno) 
to venture and explore game development.

What began as a simple one-day game project to build a simple game, evolved into a more ambitious goal: building a game 
engine from the ground up. I didn't want to use Unity or UE, as I wanted to know how the inner mechanics of game 
engines and game systems work.

## Development

Development has ceased on this project as it was primarily a prototype task and I had achieved my goals from this task. It 
served as a valuable learning experience and stepping stone for the future development of 
[NGEN](https://github.com/s-mcdonald/NGEN) (Neon Game ENgine). 

Which will incorporate the strengths and successful components of this work in addition to new features such as 3D, 
mesh rendering, Camera support and more.

## Checkout and Build
#### Step 1: Clone with --recursive

Recursively clone the repo as the repo contains submodules.

```
git clone --recursive https://github.com/s-mcdonald/NeonVoid.git
```




#### Step 2: Linux Build
```shell
cd ./NeonVoid/scripts
sudo ./linux_install.sh
sudo ./linux_build.sh
```

#### Step 2: Windows Build
```shell
cd .\NeonVoid\scripts
.\windows_install.bat
.\windows_build_vs2019.bat
```

For Windows, you have a couple of options for different Visual Studio versions.

| Visual Studio | Command                              |
|---------------|--------------------------------------|
| 2019          | `./scripts/windows_build_vs2019.bat` |
| 2022          | `./scripts/windows_build_vs2022.bat` |




### OS and Backend API Support


| API         | Platforms               | Supported     | Resources                                       |
|-------------|-------------------------|---------------|-------------------------------------------------|
| OpenGL 3.3+ | Linux, Windows          | **Yes**       | [OpenGL Website](https://www.opengl.org/)                           |
| DirectX     | Windows                 | <sub>No</sub> | [NVIDIA Docs](https://developer.nvidia.com/directx), [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/directx)       |
| Vulkan      | Linux, Windows, Android | <sub>No</sub> | [Vulkan Website](https://www.vulkan.org/)                           |


| OS      | Version         | Supported |
|---------|-----------------|-----------|
| Windows | 7+              | **Yes**   |
| Linux   | Debian / Ubuntu | **Yes**   |
| MacOS   |                 | No        |


### CMake Project files

CMake project: Has been described to set up the three projects listed below ;
- Game
- GameEngine
- NeonRuntime


### Resources & Reference

#### 3rd Party Libs

| Library   | Website                                      | GitHub | Purpose                       |
|-----------|----------------------------------------------|--------|-------------------------------|
| glad      | [Website](https://glad.dav1d.de/)           | [Repository](https://github.com/Dav1dde/glad) | OpenGL initialization  |
| glfw      | [Website](https://www.glfw.org/)           | [Repository](https://github.com/glfw/glfw) | GL Context / Window etc. |
| glm       | [Website](https://glm.g-truc.net/)           | [Repository](https://github.com/icaven/glm) | Math library  |
| miniaudio | [Website](https://miniaud.io/)           | [Repository](https://github.com/mackron/miniaudio) | Audio playback   |
| fkYAML    | [Website](https://fktn-k.github.io/fkYAML/)  | [Repository](https://github.com/fktn-k/fkYAML) | YAML I/O  |
| FT        | [Website](https://freetype.org/)  | [Repository](https://github.com/freetype/freetype) | Text rendering                |


#### Resources

* [pixabay.com](https://pixabay.com/sound-effects/)
* [OpenGameArt](https://opengameart.org/)


#### References

| Tool | Description |
|------|-------------|
| [CMake Tools](https://cmake.org/download/) | Build system generator |
| [CLang-format](https://clang.llvm.org/docs/ClangFormat.html) | Code formatting tool |
| [DocsGL](http://docs.gl/) | OpenGL documentation |
| [OpenGL](https://www.opengl.org/) | Graphics API documentation |
| [Valgrind](https://valgrind.org/) | Memory leak checker (Linux) |
| [DrMemory](https://drmemory.org) | Memory leak checker (Windows/Linux) |

### LICENCE
[MIT](LICENSE)