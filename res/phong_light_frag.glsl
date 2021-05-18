/************************************
* Simple Phong model fragment shader
*
************************************/

#version 430 core


in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 lightColor;
uniform vec3 lampPos;

const vec3 defaultObjectColor = vec3(0.494, 0.486, 0.455);
const float ambientStrength = 0.5f;


void main(void) {		
	
	// ambient
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lampPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);	// diffuse impact via dot product (refer to angle theta in tutorial)
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * defaultObjectColor;
	fragColor = vec4(result, 1.0f);		
}

