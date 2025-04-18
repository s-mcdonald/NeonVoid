# NeonVoid

> **Pre alpha:** This project is in active development and does not yet have a stable release.

A simple GameEngine written in C++.

### OS Support
Eventually this will support Windows and Linux OS. I am currently in phase 1, development so only OpenGL at this time on linux.

### Build System

The current Build system is CMake using the CMakeList.txt to structure the projects.
I do have plans to convert this to PreMake.
For now a single CMake project, the CMakeList.txt file, will set up all project 3 ;
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