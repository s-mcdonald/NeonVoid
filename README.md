# NeonVoid

> **Note:** This project is for educational purposes and is currently in active development.

A simple 2D GameEngine written in C++.

## About NeonVoid Engine

This project started as a personal journey to learn C++. It's been many years since playing around with a compiled lang, 
and in more recent years I have only been working with web development, and was inspired by a 
YouTuber [The Cherno](https://github.com/thecherno) to venture into game development.

What began as a simple one-day game project evolved into a more ambitious goal: building a game engine from scratch. 
While I'm neither a game developer nor a C++ programmer, I chose to challenge myself by designing the engine 
architecture independently.


### OS Support
Eventually this will support Windows and Linux OS. I am currently in phase 1, development so only OpenGL at this time on linux.

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

### Backend API Support

> **Note:** This project is still in early development of phase 1.


| Phase | API | Platforms | Status | Resources |
|-------|-----|-----------|---------|-----------|
| 1 | OpenGL 3.3+ | Linux, Windows | **In Development** | [OpenGL Website](https://www.opengl.org/) |
| 2 | DirectX | Windows | <sub>Not Started</sub> | [NVIDIA Docs](https://developer.nvidia.com/directx), [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/directx) |
| 3 | Vulkan | Linux, Windows, Android | <sub>Not Started</sub> | [Vulkan Website](https://www.vulkan.org/) |



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


#### General Source Code Style
- Using `*.hpp` for c++ headers.
- Header files will be located within the `include` dir of the respective project.
- Purposefully used only raw pointers, no smart pointers/shared pointers in this codebase.
- Member Variables `m_` on stack or must be cleaned up by the owning obejct, `mx_` are not owned by the object.

#### Resources
List of websites where we may source content from for demonstration and included in this repo.

* [pixabay.com](https://pixabay.com/sound-effects/)


#### References
 - [Download CMake Tools](https://cmake.org/download/)
 - [CLang-format](https://clang.llvm.org/docs/ClangFormat.html)
 - [DocsGL](http://docs.gl/)
 - [OpenGL Docs](https://www.opengl.org/)


### LICENCE
- [MIT](LICENSE)