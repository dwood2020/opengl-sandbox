#include "Lighting.h"


Lighting::Lighting(): direction(glm::vec3(0.0f)), color(glm::vec3(1.0f)), ambient(0.5f) { }


Lighting::~Lighting() { }


void Lighting::SetDirection(const glm::vec3& direction) {
	this->direction = direction;
}


void Lighting::SetColor(const glm::vec3& color) {
	this->color = color;
}


void Lighting::SetAmbientFactor(float ambient) {
	this->ambient = ambient;
}


void Lighting::SetUniforms(ShaderProgram& shaderProg) const {
	shaderProg.SetUniformVec3("directionalLight.direction", direction);
	shaderProg.SetUniformVec3("directionalLight.color", color);
	shaderProg.SetUniformFloat("directionalLight.ambientFactor", ambient);
}
