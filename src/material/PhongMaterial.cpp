#include "PhongMaterial.h"
#include <utility>


PhongMaterial::PhongMaterial(ShaderProgram* shaderProgram): MaterialBase(shaderProgram) {
	hasDiffuseTexture = false;
	hasSpecularTexture = false;

	SetAffectedByLight(true);	

	// set the default values
	SetUniform(diffuseName, MaterialUniform(glm::vec3(0.0f)));
	SetUniform(specularName, MaterialUniform(glm::vec3(0.0f)));
	SetUniform(shininessName, MaterialUniform(32.0f));

	SetUniform(hasDiffuseTextureName, MaterialUniform((int)hasDiffuseTexture));
	SetUniform(useTexCoordsName, MaterialUniform((int)hasDiffuseTexture));
}


PhongMaterial::~PhongMaterial() { }


void PhongMaterial::SetDiffuseColor(const glm::vec3& diffuse){	
	SetUniform(diffuseName, MaterialUniform(diffuse));
}


void PhongMaterial::SetDiffuseTexture(const Texture& diffuse){
	hasDiffuseTexture = true;
	SetTexture(diffuse);
	SetUniform(hasDiffuseTextureName, MaterialUniform((int)hasDiffuseTexture));
	SetUniform(useTexCoordsName, MaterialUniform((int)hasDiffuseTexture));
}


void PhongMaterial::SetSpecularColor(const glm::vec3& specular) {
	SetUniform(specularName, MaterialUniform(specular));
}


void PhongMaterial::SetSpecularTexture(const Texture& specular) {
	//TODO: handle the set order. Specular can only be set when diffuse is set!!
}


void PhongMaterial::SetShininess(float shininess) {
	SetUniform(shininessName, MaterialUniform(shininess));
}

