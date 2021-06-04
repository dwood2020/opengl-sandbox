#version 430 core

in vec3 vertexColor;

out vec4 fragColor;

uniform vec3 color;
uniform int useColorVertices;


void main(void) {

	if (useColorVertices == 1) {
		fragColor = vec4(vertexColor, 1.0f);
	}
	else {
		fragColor = vec4(color, 1.0f);	
	}

	
}

