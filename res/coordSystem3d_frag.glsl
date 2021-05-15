#version 430 core


out vec4 fragColor;

in vec3 currentColor;


void main(void) {	

	fragColor = vec4(currentColor, 1.0f);
}