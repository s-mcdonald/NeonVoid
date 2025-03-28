# NeonVoid (Work in progress)

> **Pre alpha:** This project is in active development and does not yet have a stable release.

An attempt at a OGL C++ retro game(/engine).

NeonVoid is a side project I'm currently developing. It's intended to be both a game and a game engine, inspired by 80s arcade games. My goal is to create a framework that makes building retro-style games fun, simple with clean code. Additionally, if the project evolves, I plan to incorporate advanced features like HDR and Bloom effects to enhance the visual experience.
A real-time scene editor using Imgui to build scenes and levels.

### Build System

Then run build script (depending if you are running Windows or a Linux system, choose the script wisely).

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


### Sound
Currently sound files are sourced from the below websites ;;

* [pixabay.com](https://pixabay.com/sound-effects/)


### A note on header files
Using *.hpp for c++ headers or no extension at all, and for c the extension should be *.h


### LICENCE
[MIT](LICENSE)


### Other Resources
[Download Cmake Tools](https://cmake.org/download/)