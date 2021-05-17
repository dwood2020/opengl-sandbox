#version 430 core

layout (location = 0) in vec3 aPos;


uniform mat4 M;
uniform mat4 PV;


void main(void) {

	vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	pos = PV * M * pos;
	
	gl_Position = pos;
}

