#include "PhongMaterial.h"
#include <utility>


PhongMaterial::PhongMaterial(ShaderProgram* shaderProgram): MaterialBase(shaderProgram) {
	hasDiffuseTexture = false;
	hasSpecularTexture = false;

	SetAffectedByLight(true);	

	// set the default values
	SetUniform(diffuseName, Uniform(glm::vec3(0.0f)));
	SetUniform(specularName, Uniform(glm::vec3(0.0f)));
	SetUniform(shininessName, Uniform(32.0f));

	SetUniform(hasDiffuseTextureName, Uniform((int)hasDiffuseTexture));
	SetUniform(useTexCoordsName, Uniform((int)hasDiffuseTexture));
}


PhongMaterial::~PhongMaterial() { }


void PhongMaterial::SetDiffuseColor(const glm::vec3& diffuse){	
	SetUniform(diffuseName, Uniform(diffuse));
}


void PhongMaterial::SetDiffuseTexture(const Texture& diffuse){
	hasDiffuseTexture = true;
	SetTexture(diffuse);
	SetUniform(hasDiffuseTextureName, Uniform((int)hasDiffuseTexture));
	SetUniform(useTexCoordsName, Uniform((int)hasDiffuseTexture));
}


void PhongMaterial::SetSpecularColor(const glm::vec3& specular) {
	SetUniform(specularName, Uniform(specular));
}


void PhongMaterial::SetSpecularTexture(const Texture& specular) {
	//TODO: handle the set order. Specular can only be set when diffuse is set!!
}


void PhongMaterial::SetShininess(float shininess) {
	SetUniform(shininessName, Uniform(shininess));
}

