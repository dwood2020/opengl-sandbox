#version 430 core

layout (location = 0) in vec3 aPos;


uniform mat4 M;
uniform mat4 PV;


void main(void) {
	
	vec4 pos = PV * M * vec4(aPos, 1.0);	
	gl_Position = pos;
}