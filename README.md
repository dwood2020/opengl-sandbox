# opengl-sandbox
Personal OpenGL Sandbox.   
Currently only as Visual Studio 2019 project, CMake support will be added in the future.   

## Goal
The aim of this project is to implement different techniques commonly used in rendering engines and to provide a "sandbox" 
for testing and showcasing.  
These implementations are definitely no perfectly engineered code. This is a learning project.

## Implemented features:
####Window abstraction   
The GUI library IUP (<https://www.tecgraf.puc-rio.br/iup/>) is used for a rudimentary GUI and to provide an OpenGL context.
The entire window logic is abstracted away in a "window class".

####OpenGL shader abstraction
The OpenGL shaders and shader programs are encapsulated in entitled classes.

####Event system
A simple event system in a bus topology is implemented. Events are triggered by user interaction (e.g. mouse moving, clicking, 
resizing the window, ...). 
All relevant components of the program are connected to the event bus and act as "listeners". Control flow by an excessive amount of 
callbacks is avoided.

####Camera system
A simple user input-controlled camera system is implemented. The camera rotates on a sphere around a target point while
the target point itself can be shifted ("pan").

####Material system
A simple material system is implemented, following the general interpretation: *Material = Shader + Uniforms*.
Uniforms which define a material are ownded by the material itself.


---

Readme is WIP
