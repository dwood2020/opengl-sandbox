/**********************************************
* Phong model fragment shader
* Including material
*
**********************************************/

#version 430 core


in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;


struct Material {
	//vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;
	vec3 color;
	float ambientFactor;
};

uniform Material material;
uniform DirectionalLight directionalLight;
uniform vec3 viewPos;


void main(void) {		
	
	// ambient	
	vec3 ambient = directionalLight.ambientFactor * directionalLight.color * material.diffuse;

	// diffuse
	vec3 norm = normalize(normal);					// normalized normals	
	vec3 lightDir = normalize(-directionalLight.direction);
	float diff = max(dot(norm, lightDir), 0.0f);	// diffuse impact via dot product (refer to angle theta in tutorial)		
	vec3 diffuse = directionalLight.color * (diff * material.diffuse);

	// specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);		// negated lightDir, as reflect() expects vector FROM light source TO fragment
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);	
	vec3 specular = directionalLight.color * (spec * material.specular);


	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0f);		
}

