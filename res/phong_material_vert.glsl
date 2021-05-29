#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTEST;
layout (location = 2) in vec3 aNormal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 M;
uniform mat4 PV;


void main(void) {
	
	vec4 fragPos4 = M * vec4(aPos, 1.0f);	
	fragPos = vec3(fragPos4.x, fragPos4.y, fragPos4.z);	//This syntax is somehow needed on OpenGL 4.3?

	normal = mat3(M) * aNormal;	// if non-uniform scaling is applied, this cannot be done. A normal matrix is needed (transposed inverse of M)

	vec4 pos = PV * M * vec4(aPos, 1.0f);	
	gl_Position = pos;
	
}

