#version 430 core

layout (location = 0) in vec3 aPos;

out vec3 coordsTest;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(void) {
	
	vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	
	gl_Position = P * V * M * pos;
}