# opengl-sandbox    
Personal OpenGL Sandbox.    
Object-oriented implementation of basic rendering functionalities, done as university project on efficient programming.    
This project uses CMake as build system. The supported compilers are MinGW, MSVC on Windows and GCC on Linux (tested on Lubuntu).
A Visual Studio solution file is also provided.    
For simplicity, required library files are contained within this repository.    

![Screenshot](/img/screenshot.png "Project screenshot")

## Overview    
- [Goal](##goal)
- [Implemented features](##implemented-features)
- [Build instructions](##build-instructions)
- [Code documentation](##code-documentation)
- [Third-party dependencies](##third-party-dependencies)

---

## Goal   
The aim of this project is to implement different techniques commonly used in rendering engines and to provide a "sandbox" 
for testing and showcasing.  
These implementations are definitely no perfectly engineered code. This is a learning project.

## Implemented features:   
#### Window abstraction    

The GUI library [IUP](https://www.tecgraf.puc-rio.br/iup/) is used for a rudimentary GUI and to provide an OpenGL context.
The entire window logic is abstracted away in a "window class".

#### OpenGL shader abstraction   
The OpenGL shaders and shader programs are encapsulated in entitled classes.

#### Event system   
A simple event system in a bus topology is implemented. Events are triggered by user interaction (e.g. mouse moving, clicking, 
resizing the window, ...). 
All relevant components of the program are connected to the event bus and act as "listeners". Control flow by an excessive amount of 
callbacks is avoided.

#### Camera system   
A simple user input-controlled camera system is implemented. The camera rotates on a sphere around a target point while
the target point itself can be shifted ("pan").   
The implementation contains perspective and orthogonal camera projection modes and their handling.

#### Material system   
A simple material system is implemented, following the general interpretation: *Material = Shader + Uniforms*.
Uniforms which define a material are ownded by the material itself.    
Currently, flat materials and [Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) model materials are implemented (see `FlatMaterial` and `PhongMaterial` classes).

#### Simple Voxel World Grid   
A simple voxel grid is defined from which voxel meshes are generated. 
Currently, the grid definition consists of 8x8x8 block sections which are simply held in a `std::map` and consist of flat `char` arrays.

#### 3D object selection    
A simple object selection via a casted ray is implemented for blocks which are contained in the voxel grid. 
The implementation makes a block selectable directly in the 3D rendering. It works by iterating through the grid along a ray.
(The selection logic is encapsulated within `MouseSelector`).

---
## Build instructions   
**NOTE**: All instructions here show how to build a Release build. Debug builds can be built by changing the according CMake parameters.   

#### Windows - MSVC/Visual Studio
```
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build . --config Release -j
```

#### Windows - MinGW
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release -j
```

#### Linux - GCC
```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
cmake --build . --config Release -j
```

**NOTE**: Currently the resource folder `res` needs to be manually copied to the executable directory before running.    
This will be changed in the future.   
Copying can be manually done with e.g. `scp -r ./res ./build/res`

---

## Code documentation
Doxygen HTML code documentation can be generated with the included Doxyfile:
```
doxygen Doxyfile
```

---

## Third-party dependencies   
All dependent libraries are included within this repository, see `LICENSES.txt`.   

- IUP: <https://www.tecgraf.puc-rio.br/iup/>
- GLAD: <https://github.com/dav1dde/glad-web>
- OpenGL Mathematics (GLM): <https://github.com/g-truc/glm>
- stb_image.h: <https://github.com/nothings/stb>
- Bresenham Algorithm by Will Navidson (currently not in use but part of the source files): <https://gist.github.com/yamamushi/5823518>
---