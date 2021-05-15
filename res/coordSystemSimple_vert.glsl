#version 430 core

layout (location = 0) in vec3 aPos;


uniform mat4 M;
uniform mat4 PV;

out vec3 axisColor;

const vec3 colorX = vec3(1.0f, 0.0f, 0.0f);
const vec3 colorY = vec3(0.0f, 1.0f, 0.0f);
const vec3 colorZ = vec3(0.0f, 0.0f, 1.0f);

void main(void) {

	vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	pos = PV * M * pos;
	
	gl_Position = pos;

	//determine the current axis color
	if (gl_VertexID > 3) {
		// z-axis
		axisColor = colorZ;
	}
	else if (gl_VertexID > 1) {
		axisColor = colorY;
	}
	else {
		axisColor = colorX;
	}
}
