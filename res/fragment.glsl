#version 430 core

out vec4 fragColor;

in float zPos;

const vec3 defaultColor = vec3(0.494, 0.486, 0.455);
const vec3 redColor = vec3(1.0f, 0.0f, 0.0f);
const vec3 yellowColor = vec3(1.0f, 1.0f, 0.0f);


void main(void) {

	vec3 color = defaultColor;

	if (zPos > 1.0f) {
		color = yellowColor;
	}
//	else if (zPos < 0.6f) {
//		color = redColor;
//	}

	fragColor = vec4(color, 1.0f);
}

