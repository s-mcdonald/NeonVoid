# NeonVoid

> **Note:** This project is for educational purposes and is currently in active development.

A simple 2D GameEngine written in C++.

## About NeonVoid Engine

This project started as a personal journey to learn C++. I had been inspired by the
YouTuber [The Cherno](https://github.com/thecherno) to venture and explore game development.

What began as a simple one-day game project to build a simple game, evolved into a more ambitious goal: building a game engine from the ground up.
I didn't want to use Unity or UE, as I wanted to know how the inner mechanics of game engines and systems worked.


### OS Support
Eventually, this project will support both Windows and Linux OS. I am currently in phase 1 and only developing on Linux currently.
Once the project is in a state where a simple game can be developed, i will switch over to Windows to build in support and compatibility.

It is unlikely I will ever get to implement DX or Vulkan; however, the project has been built to support it from the beginning.


### Backend API Support

> **Note:** This project is still in early development of phase 1.


| Phase | API | Platforms | Status | Resources |
|-------|-----|-----------|---------|-----------|
| 1 | OpenGL 3.3+ | Linux, Windows | **In Development** | [OpenGL Website](https://www.opengl.org/) |
| 2 | DirectX | Windows | <sub>Not Started</sub> | [NVIDIA Docs](https://developer.nvidia.com/directx), [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/directx) |
| 3 | Vulkan | Linux, Windows, Android | <sub>Not Started</sub> | [Vulkan Website](https://www.vulkan.org/) |


### Build System

A single CMake project, the `CMakeLists.txt` has been described to set up all three projects listed below ;
- Game
- GameEngine (static lib)
- NeonRuntime (static lib)


#### Linux
```
./scripts/build.sh
```

#### Windows
There are a couple of VS options, select the one that suits your needs or modify as required.
```
./scripts/setup-vs-2022.bat 
```

### Game Engine Features

| Features                                                 |
|----------------------------------------------------------|
| Collision Detection
| Composable Entities
| Separation of Runtime by Backend 



### Resources & Reference

#### 3rd Party Libs

| Library | Website | GitHub | Purpose |
|---------|---------|--------|----------|
| glad | [Website](https://glad.dav1d.de/) | [Repository](https://github.com/Dav1dde/glad) | OpenGL initialization |
| glfw | [Website](https://www.glfw.org/) | [Repository](https://github.com/glfw/glfw) | GL Context / Window etc. |
| glm | [Website](https://glm.g-truc.net/) | [Repository](https://github.com/icaven/glm) | Math library |
| miniaudio | [Website](https://miniaud.io/) | [Repository](https://github.com/mackron/miniaudio) | Audio playback |
| fkYAML | [Website](https://fktn-k.github.io/fkYAML/) | [Repository](https://github.com/fktn-k/fkYAML) | YAML I/O |
| stb | - | [Repository](https://github.com/nothings/stb) | Text rendering |


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
- [MIT](LICENSE)