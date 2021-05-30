#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoords;

uniform mat4 M;
uniform mat4 PV;

uniform int useTexCoords = 0;


void main(void) {
	
	vec4 fragPos4 = M * vec4(aPos, 1.0f);	
	fragPos = vec3(fragPos4.x, fragPos4.y, fragPos4.z);	//This syntax is somehow needed on OpenGL 4.3?

	normal = mat3(M) * aNormal;	// if non-uniform scaling is applied, this cannot be done. A normal matrix is needed (transposed inverse of M)

	// gather texture coords if needed, do not touch aTexCoords otherwise
	if (useTexCoords != 0) {
		texCoords = aTexCoords;
	}

	vec4 pos = PV * M * vec4(aPos, 1.0f);	
	gl_Position = pos;
	
}

