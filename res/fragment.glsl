#version 450 core

out vec4 fragColor;

in vec3 coordsTest;

uniform float uniformAlpha;


void main(void) {
	fragColor = vec4(1.0f*coordsTest.x, 1.0f*coordsTest.y, 1.0f*uniformAlpha, 1.0f*uniformAlpha);
}

