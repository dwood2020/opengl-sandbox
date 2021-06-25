#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aColor;


out vec3 vertexColor;

uniform mat4 M = mat4(1.0f);
uniform mat4 PV;
uniform int useColorVertices;


void main(void) {

	vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	pos = PV * M * pos;
	
	gl_Position = pos;

	if (useColorVertices == 1) {
		vertexColor = aColor;
	}
}

