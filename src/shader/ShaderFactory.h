#pragma once
#include <memory>
#include <string>
#include "ShaderProgram.h"

//TODO: Might move this into the material system later? &rename to "MaterialShaderFactory" or so

class ShaderFactory final {
private:
	const std::string phongVertSourePath = "res/phong_material_vert.glsl";
	const std::string phongFragSourcePath = "res/phong_material_frag.glsl";

public:
	ShaderFactory();
	~ShaderFactory();

	std::unique_ptr<ShaderProgram> MakePhongShaderProgram(void) const;
};