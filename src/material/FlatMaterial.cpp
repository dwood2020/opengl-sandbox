#include "FlatMaterial.h"


FlatMaterial::FlatMaterial(ShaderProgram& shaderProgram): MaterialBase(shaderProgram) {
	useColorVertices = false;

	SetAffectedByLight(false);

	SetUniform(colorName, Uniform(glm::vec3(1.0f)));
	SetUniform(hasTextureVerticesName, Uniform((int)useColorVertices));
}


FlatMaterial::~FlatMaterial() { }


void FlatMaterial::SetFlatColor(const glm::vec3& color) {
	SetUniform(colorName, Uniform(color));
}


void FlatMaterial::SetUseColorVertices(bool set) {
	useColorVertices = true;
	SetUniform(hasTextureVerticesName, Uniform((int)useColorVertices));
}
