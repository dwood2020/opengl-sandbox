#include "FlatMaterial.h"


FlatMaterial::FlatMaterial(ShaderProgram& shaderProgram): MaterialBase(shaderProgram) {
	SetUniform(colorName, Uniform(glm::vec3(0.0f)));
}


FlatMaterial::~FlatMaterial() { }


void FlatMaterial::SetFlatColor(const glm::vec3& color) {
	SetUniform(colorName, Uniform(color));
}
