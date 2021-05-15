#version 430 core

out vec4 fragColor;

in vec3 axisColor;


void main(void) {	

	fragColor = vec4(axisColor, 1.0f);
}

