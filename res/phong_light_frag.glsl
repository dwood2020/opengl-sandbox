/************************************
* Simple Phong model fragment shader
*
************************************/

#version 430 core

out vec4 fragColor;

uniform vec3 lightColor;

const vec3 defaultObjectColor = vec3(0.494, 0.486, 0.455);
const float ambientStrength = 0.5f;


void main(void) {		

	vec3 ambient = ambientStrength * lightColor;



	vec3 result = ambient * defaultObjectColor;
	fragColor = vec4(result, 1.0f);
}

