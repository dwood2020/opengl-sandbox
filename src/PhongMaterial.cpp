#include "PhongMaterial.h"


PhongMaterial::PhongMaterial(ShaderProgram& shaderProgram): MaterialBase(shaderProgram) {
	hasDiffuseTexture = false;
	hasSpecularTexture = false;
}


PhongMaterial::~PhongMaterial() { }


void PhongMaterial::SetDiffuseColor(const glm::vec3& diffuse){
	
}


void PhongMaterial::SetDiffuseTexture(const Texture& diffuse){

}


void PhongMaterial::SetSpecularColor(const glm::vec3& specular) {

}


void PhongMaterial::SetSpecularTexture(const Texture& specular) {

}


void PhongMaterial::SetShininess(float shininess) {

}
