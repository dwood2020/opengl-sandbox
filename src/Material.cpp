#include "Material.h"


Material::Material(): diffuseColor(glm::vec3(0.0f)), specularColor(glm::vec3(0.0f)), shininess(32.0f) { }


Material::~Material() { }


void Material::SetDiffuseColor(const glm::vec3& diffuse) {
	diffuseColor = diffuse;
}


void Material::SetSpecularColor(const glm::vec3& specular) {
	specularColor = specular;
}


void Material::SetShininess(float shininess) {
	this->shininess = shininess;
}


void Material::SetUniforms(ShaderProgram& shaderProg) const {
	shaderProg.SetUniformVec3("material.diffuse", diffuseColor);
	shaderProg.SetUniformVec3("material.specular", specularColor);
	shaderProg.SetUniformFloat("material.shininess", shininess);	
}
