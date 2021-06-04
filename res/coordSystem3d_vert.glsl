#version 430 core

// NOTE: This shader is currently unused.

layout (location = 0) in vec3 aPos;

uniform mat4 M;
uniform mat4 PV;

out vec3 currentColor;

const vec3 colorX = vec3(1.0f, 0.0f, 0.0f);
const vec3 colorY = vec3(0.0f, 1.0f, 0.0f);
const vec3 colorZ = vec3(0.0f, 0.0f, 1.0f);


void main(void) {
	// position
	vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	pos = PV * M * pos;	
	gl_Position = pos;

	// color
	if (gl_VertexID >= 20) {
		// x-axis
		currentColor = colorX;
	}
	else if (gl_VertexID >= 10) {
		currentColor = colorZ;
	}
	else {
		currentColor = colorY;
	}

}