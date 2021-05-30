#include "Material.h"


//Material::Material() { }


Material::Material(const ShaderProgram& shaderProg): shaderProg(&shaderProg),
	diffuseColor(glm::vec3(0.0f)), specularColor(glm::vec3(0.0f)), shininess(32.0f),
	hasDiffuseTexture(false), hasSpecularTexture(false), diffuseTexture(nullptr), specularTexture(nullptr) { }


Material::~Material() { }


void Material::SetDiffuseColor(const glm::vec3& diffuse) {
	diffuseColor = diffuse;
}


void Material::SetDiffuseTexture(const Texture& diffuse) {
	diffuseTexture = &diffuse;
	hasDiffuseTexture = true;
}


void Material::SetSpecularColor(const glm::vec3& specular) {
	specularColor = specular;
}


void Material::SetSpecularTexture(const Texture& specular) {
	specularTexture = &specular;
	hasSpecularTexture = true;
}


void Material::SetShininess(float shininess) {
	this->shininess = shininess;
}


void Material::SetUniforms() {
	shaderProg->SetUniformVec3("material.diffuseColor", diffuseColor);
	shaderProg->SetUniformVec3("material.specularColor", specularColor);
	shaderProg->SetUniformFloat("material.shininess", shininess);	

	shaderProg->SetUniformInt("material.hasDiffuseTexture", (int)hasDiffuseTexture);
	shaderProg->SetUniformInt("useTexCoords", (int)hasDiffuseTexture);	
}


void Material::BindTextures(void) const {
	if (hasDiffuseTexture) {
		diffuseTexture->Bind();
	}
}
