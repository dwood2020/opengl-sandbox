/**********************************************
* Phong model fragment shader
* Including material
*
**********************************************/

#version 430 core


in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

out vec4 fragColor;


struct Material {
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
	int hasDiffuseTexture;
	sampler2D diffuseTexture;
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
	vec3 ambient;
	if (material.hasDiffuseTexture == 1) {
		ambient = directionalLight.ambientFactor * directionalLight.color * material.diffuseColor * vec3(texture(material.diffuseTexture, texCoords));
	}
	else {
		ambient = directionalLight.ambientFactor * directionalLight.color * material.diffuseColor;
	}


	// diffuse
	vec3 norm = normalize(normal);					// normalized normals	
	vec3 lightDir = normalize(-directionalLight.direction);
	float diff = max(dot(norm, lightDir), 0.0f);	// diffuse impact via dot product (refer to angle theta in tutorial)
	
	vec3 diffuse;
	if (material.hasDiffuseTexture == 1) {
		diffuse = directionalLight.color * (diff * material.diffuseColor * vec3(texture(material.diffuseTexture, texCoords)));
	}
	else {
		diffuse = directionalLight.color * (diff * material.diffuseColor);	
	}
	

	// specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);		// negated lightDir, as reflect() expects vector FROM light source TO fragment
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);	
	vec3 specular = directionalLight.color * (spec * material.specularColor);


	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0f);		
}

