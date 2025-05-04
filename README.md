# NeonVoid

> **Note:** This project is for educational purposes and is currently in active development.

A simple 2D GameEngine written in C++.

## About NeonVoid Engine

This project started as a personal journey to learn C++. I had been inspired by the
YouTuber [The Cherno](https://github.com/thecherno) to venture and explore game development.

What began as a simple one-day game project to build a simple game, evolved into a more ambitious goal: building a game engine from the ground up.
I didn't want to use Unity or UE, as I wanted to know how the inner mechanics of game engines and game systems work.

### Clone with --recursive

You need to recursively clone the repo as I do have a couple of submodules installed for the libs.

```
git clone --recursive https://github.com/s-mcdonald/NeonVoid.git
```

### OS Support
Eventually, this project will support both Windows and Linux OS. I am currently in phase 1 and only developing on Linux currently.
Once the project is in a state where a simple game can be developed, I will switch over to Windows to build in support and compatibility.

It is unlikely I will ever get to implement DX or Vulkan; however, the project has been built to support it from the beginning.


### Backend API Support


 | API         | Platforms | Status                 | Resources |
 |-------------|-----------|------------------------|-----------|
 | OpenGL 3.3+ | Linux, Windows | **working**            | [OpenGL Website](https://www.opengl.org/) |
 | DirectX     | Windows | <sub>Not Started</sub> | [NVIDIA Docs](https://developer.nvidia.com/directx), [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/directx) |
 | Vulkan      | Linux, Windows, Android | <sub>Not Started</sub> | [Vulkan Website](https://www.vulkan.org/) |


### Build

CMake project: Has been described to set up the three projects listed below ;
- Game
- GameEngine 
- NeonRuntime

#### Linux Build
```shell
git clone --recursive https://github.com/s-mcdonald/NeonVoid.git
cd NeonVoid/scripts
sudo ./linux_install.sh
sudo ./linux_build.sh
```

#### Windows Build
```shell
git clone --recursive https://github.com/s-mcdonald/NeonVoid.git
cd NeonVoid\scripts
windows_install.bat
setup-vs-2019.bat
```

For Windows, you have a couple of options for different Visual Studio versions.

| Visual Studio | Command                       |
|---------------|-------------------------------|
| 2019          | `./scripts/setup-vs-2019.bat` |
| 2022          | `./scripts/setup-vs-2022.bat` |




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