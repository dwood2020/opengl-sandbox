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


void Lighting::SetUniforms(ShaderProgram* shaderProg) const {
	if (shaderProg == nullptr) {
		return;
	}
	shaderProg->SetUniformVec3(shaderProg->GetUniformLocation("directionalLight.direction"), direction);
	shaderProg->SetUniformVec3(shaderProg->GetUniformLocation("directionalLight.color"), color);
	shaderProg->SetUniformFloat(shaderProg->GetUniformLocation("directionalLight.ambientFactor"), ambient);
}
