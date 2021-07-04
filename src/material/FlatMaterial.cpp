#include "FlatMaterial.h"
#include <utility>


FlatMaterial::FlatMaterial(ShaderProgram* shaderProgram): MaterialBase(shaderProgram) {
	useColorVertices = false;

	SetAffectedByLight(false);

	SetUniform(colorName, MaterialUniform(glm::vec3(1.0f)));
	SetUniform(hasTextureVerticesName, MaterialUniform((int)useColorVertices));
}


FlatMaterial::~FlatMaterial() { }


void FlatMaterial::SetFlatColor(const glm::vec3& color) {
	SetUniform(colorName, MaterialUniform(color));
}


void FlatMaterial::SetUseColorVertices(bool set) {
	useColorVertices = true;
	SetUniform(hasTextureVerticesName, MaterialUniform((int)useColorVertices));
}
