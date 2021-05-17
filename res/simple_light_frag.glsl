#version 430 core

out vec4 fragColor;

uniform vec3 lightColor;

const vec3 defaultObjectColor = vec3(0.494, 0.486, 0.455);


void main(void) {		

	fragColor = vec4(lightColor * defaultObjectColor, 1.0f);
}

