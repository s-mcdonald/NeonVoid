# NeonVoid (Work in progress)

An attempt at a OGL c++ retro game(/engine).

NeonVoid is a side project I'm currently developing. It's intended to be both a game and a game engine, inspired by 80s arcade games. My goal is to create a framework that makes building retro-style games fun, simple with clean code. Additionally, if the project evolves, I plan to incorporate advanced features like HDR and Bloom effects to enhance the visual experience.
A real time scene editor using Imgui to build scenes and levels.


### Goals (Must haves)

```
[x] OpenGL/DirectX Abstraction Layer
[x] Render
  [x] - Render OGL Window
  [x] - Render Basic Shader
  [ ] - Render Shader Component
[x] Render Basic Shape on a via Shape->Component
[ ] Input Control
  [ ] - Keyboard Input (scene)
  [ ] - Mouse Button Input (scene)
  [ ] - Mouse Wheel Input (scene)
[ ] Scoreboard (On Screen display + HUD) - Component
  [ ] - Player Health
  [ ] - Player Score
  [ ] - Player Bonus XP
  [ ] - Player Toolbelt (Chest)
[ ] Basic Collision Detecton
[x] Audio System (initial, needs refactoring)
  [ ]  - Scene background audio
  [ ]  - Component Sound effects
  [ ]  - Custom audio sounds
[ ] Title Scene
[ ] Menu Scene  
[ ] Save / Load Games 
[ ] Configurable Levels via Yaml
```

Nice to haves

### Goals (Achievable Nice to haves)
```
[ ] Game Engine UI
  [ ] - Scene building
```

### Goals (Nice to have but not required)
```
[ ] ECS
[ ] Multi Levels (Multi Scene)
[ ] Physics Engine
[ ] DirectX rendering
```

### Build & Compile
First initialize CMakeList
```sh
cmake .
```

Then run build script (depending if you are running Windows or a Linux system, choose the script wisely).

#### Linux
```
./scripts/build.sh
```

#### Windows
```
./scripts/build.bat
```

### Libs

The below libs are required to build.
Future updates will see these libs source code included in the repo.

* [glew](https://github.com/nigels-com/glew)
* [glm](https://github.com/icaven/glm)
* [minaudio](https://miniaud.io/) (https://github.com/mackron/miniaudio)


### Sound
Currently sound files are sourced from the below websites ;;

* [pixabay.com](https://pixabay.com/sound-effects/)


### A note on header files
Using *.hpp for c++ headers or no ext at all, and for c the ext shound be *.h


### LICENCE
MIT