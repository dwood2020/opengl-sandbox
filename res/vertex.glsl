#version 430 core

layout (location = 0) in vec3 aPos;

out float zPos;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


void main(void) {

	vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);

	pos = P * V * M * pos;

	zPos = pos.z;
	
	gl_Position = pos;
}

