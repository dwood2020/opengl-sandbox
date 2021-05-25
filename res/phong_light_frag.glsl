/************************************
* Simple Phong model fragment shader
*
************************************/

#version 430 core


in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 lightColor;
uniform vec3 directionalLightDir;
uniform vec3 viewPos;

const vec3 defaultObjectColor = vec3(0.494, 0.486, 0.455);
const float ambientStrength = 0.5f;


void main(void) {		
	
	// ambient
	vec3 ambient = ambientStrength * lightColor * defaultObjectColor;

	// diffuse
	vec3 norm = normalize(normal);					// normalized normals
	vec3 lightDir = normalize(-directionalLightDir);
	float diff = max(dot(norm, lightDir), 0.0f);	// diffuse impact via dot product (refer to angle theta in tutorial)
	vec3 diffuse = diff * lightColor;

	// specular
	const float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);		// negated lightDir, as reflect() expects vector FROM light source TO fragment
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;


	vec3 result = (ambient + diffuse + specular) * defaultObjectColor;
	fragColor = vec4(result, 1.0f);		
}

