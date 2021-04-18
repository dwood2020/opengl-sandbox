#version 450 core

layout (location = 0) in vec3 aPos;

out vec3 coordsTest;

void main(void) {
	
	vec4 temp = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	coordsTest = temp.xyz;
	gl_Position = temp;
}