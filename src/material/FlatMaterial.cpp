#include "FlatMaterial.h"
#include <utility>


FlatMaterial::FlatMaterial(ShaderProgram* shaderProgram): MaterialBase(shaderProgram) {
	useColorVertices = false;

	SetAffectedByLight(false);

	SetUniform(colorName, MaterialUniform(glm::vec4(1.0f)));
	SetUniform(hasTextureVerticesName, MaterialUniform((int)useColorVertices));
}


FlatMaterial::~FlatMaterial() { }


void FlatMaterial::SetFlatColor(const glm::vec4& color) {
	SetUniform(colorName, MaterialUniform(color));
	if (color.w < 0.999f) {
		SetTransparent(true);
	}
	else {
		SetTransparent(false);
	}
}


void FlatMaterial::SetUseColorVertices(bool set) {
	useColorVertices = true;
	SetUniform(hasTextureVerticesName, MaterialUniform((int)useColorVertices));
}
