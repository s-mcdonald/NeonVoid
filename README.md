# NeonVoid

> **Pre alpha:** This project is in active development and does not yet have a stable release.

My first GameEngine written in C++ with support for various rendering API.

NeonVoid is a side project I'm currently developing, intended to be a game engine focused on creating retro-style 
"Space Invaders" type games. I have never built a game engine, nor game, and have no idea what I'm doing. 
But just having a tonn of fun figuring it out.


### Build System

The current Build system is CMake using the CMakeList.txt to structure the projects.
I do have future plans to convert this to PreMake

#### Linux
```
./scripts/build.sh
```

#### Windows
There are a couple of VS options, select the one that suits your needs or modify as required.
```
./scripts/setup-vs-2022.bat 
```

### Libs

* [glew](https://github.com/nigels-com/glew)
* [glfw](https://www.glfw.org/) [(github)](https://github.com/glfw/glfw)
* [glm](https://github.com/icaven/glm)
* [minaudio](https://miniaud.io/)
* [std](https://github.com/nothings/stb/tree/master)


### Sound
Currently sound files are sourced from the below websites ;;

* [pixabay.com](https://pixabay.com/sound-effects/)


### Header files
- Using `*.hpp` for c++ headers.
- Header files will be located within the same directory as the implementation only for initial dev.
- Either as the same name as the implementation file or the name of the directory its in.
  - I do plan to restructure the code so there will be /include folder for these.



### LICENCE
 - [MIT](LICENSE)


### Other Resources
 - [Download Cmake Tools](https://cmake.org/download/)
 - [CLang-format](https://clang.llvm.org/docs/ClangFormat.html)
 - [DocsGL](http://docs.gl/)
 - [OpenGL Docs](https://www.opengl.org/)