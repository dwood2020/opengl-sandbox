#version 430 core

out vec4 fragColor;


const vec3 defaultColor = vec3(0.494, 0.486, 0.455);


void main(void) {

	vec3 color = defaultColor;

	fragColor = vec4(color, 1.0f);
}

