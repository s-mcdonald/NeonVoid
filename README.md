# NeonVoid (Work in progress)

> **Pre alpha:** This project is in active development and does not yet have a stable release.

My first GameEngine written in C++ with support for various rendering API.

NeonVoid is a side project I'm currently developing. It's intended to be both a game and a game engine, 
inspired by 80s arcade space invaders type games.  My goal is to create a framework that
makes building retro-style "Space Invaders" type games.


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

The below libs are required to build.
Future updates will see these libs source code included in the repo.

* [glew](https://github.com/nigels-com/glew)
* [glm](https://github.com/icaven/glm)
* [minaudio](https://miniaud.io/)
* [std](https://github.com/nothings/stb/tree/master)


### Sound
Currently sound files are sourced from the below websites ;;

* [pixabay.com](https://pixabay.com/sound-effects/)


### Header files
- *.hpp for c++ headers
- Header files will be located within the same directory as the implementation only for initial dev.
  - I do plan to restructure the code so there will be /include folder for these.


### LICENCE
[MIT](LICENSE)


### Other Resources
 - [Download Cmake Tools](https://cmake.org/download/)
 - [CLang-format](https://clang.llvm.org/docs/ClangFormat.html)