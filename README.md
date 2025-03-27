# NeonVoid

An attempt at a OGL c++ retro game(/engine).

NeonVoid is a side project I'm currently developing. It's intended to be both a game and a game engine, inspired by 80s arcade games. My goal is to create a framework that makes building retro-style games fun, simple, and clean. Additionally, if the project evolves, I plan to incorporate advanced features like HDR and bloom effects to enhance the visual experience of these simple games, giving them a high-gloss, polished look. - if I ever get to that level.


### Goals

```
[x] Abstracted Playform for DX and OGL
[x] Render OGL Window
[x] Render Basic Shape on a via Shape->Component
[ ] Move component on screen  
[ ] Scoreboard (On Screen display)
[ ] Collision Detecton
[x] Audio Playback (initial, needs refactoring)
[ ] Title Sceen
[ ] Menu Sceen  
[ ] Save / Load Games 
[ ] Multi Levels (Multi Scene)
[ ] Configurable Levels via Yaml
[ ] Physics Engine
```

### Build & Compile
First initialize CMakeList
```sh
cmake .
```

Then run bash.sh or build.bat depending if you are running Windows or a Linux system.
```
./build.sh
```

### Libs

The below lists are required to be included but not committed to the repo.
* Glew
* std
* glm
* minaudio

#### Miniaudio - https://miniaud.io/
```
https://github.com/mackron/miniaudio
```


### A note on header files
Using *.hpp for c++ headers or no ext at all, and for c the ext shound be *.h


### LICENCE
MIT