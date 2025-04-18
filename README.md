# NeonVoid

> **Pre-alpha:** This project is in active development and does not yet have a stable release.

A simple 2D GameEngine written in C++.

# About NeonVoid Engine

This project started as a personal journey to learn C++. Coming from a web development background, I was inspired by YouTuber 
[The Cherno](https://github.com/thecherno) to venture into game development.

What began as a simple one-day game project evolved into a more ambitious goal: building a game engine from scratch. 
While I'm neither a game developer nor a C++ programmer by trade, I chose to challenge myself by designing the engine architecture independently, 
preferring to learn through experimentation rather than copying existing solutions from tutorials.
This approach, though more challenging, provides a unique learning experience and pushes me to think creatively about problem-solving in a 
native programming environment.

I do spend most of my time refactoring as I learn, so the commit history is a bit long-winded, but as the project evolves, I do see some clarity.


### OS Support
Eventually this will support Windows and Linux OS. I am currently in phase 1, development so only OpenGL at this time on linux.

### Build System

A single CMake project, the `CMakeList.txt` has been described to set up all three projects listed below ;
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
* Phase 1: >= `OpenGL 3.3` <-- in development
* Phase 2: >= `DirectX (Windows)`
* Phase 3: >= `Vulkan`


### Resources & Reference

#### 3rd Part Libs

* [glad](https://glad.dav1d.de/) [(github)](https://github.com/Dav1dde/glad) - `OpenGL initialization`
* [glfw](https://www.glfw.org/) [(github)](https://github.com/glfw/glfw) - `GL Context / Window ect`
* [glm](https://glm.g-truc.net/) [(github)](https://github.com/icaven/glm) - `Math lib`
* [minaudio](https://miniaud.io/) [(github)](https://github.com/mackron/miniaudio) - `Audio playback`
* [fkYaml](https://fktn-k.github.io/fkYAML/) [(github)](https://github.com/fktn-k/fkYAML) - `Yaml io`
* [stb](https://github.com/nothings/stb) - `Text rendering`



#### General Source Code Style
- Using `*.hpp` for c++ headers.
- Header files will be located within the `include` dir of the respective project.
- Purposefully used only raw pointers, no smart pointers/shared pointers in this codebase.

#### Resources
List of websites where we may source content from for demonstration and included in this repo.

* [pixabay.com](https://pixabay.com/sound-effects/)


#### References
 - [Download Cmake Tools](https://cmake.org/download/)
 - [CLang-format](https://clang.llvm.org/docs/ClangFormat.html)
 - [DocsGL](http://docs.gl/)
 - [OpenGL Docs](https://www.opengl.org/)


### LICENCE
- [MIT](LICENSE)