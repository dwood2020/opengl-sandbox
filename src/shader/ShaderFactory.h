#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ShaderProgram.h"

//TODO: Might move this into the material system later? &rename to "MaterialShaderFactory" or so

/// <summary>
/// This class handles shader construction and compilation.
/// It knows default shaders.
/// </summary>
class ShaderFactory final {
private:
	const std::string phongVertSourePath = "res/phong_material_vert.glsl";
	const std::string phongFragSourcePath = "res/phong_material_frag.glsl";

	const std::string flatVertSourcePath = "res/flat_material_vert.glsl";
	const std::string flatFragSourcePath = "res/flat_material_frag.glsl";

	std::vector<ShaderProgram*> refs;

public:
	ShaderFactory();
	~ShaderFactory();

	ShaderProgram* MakeDefaultPhongShaderProgram(void);

	ShaderProgram* MakeDefaultFlatShaderProgram(void);

private:
	ShaderProgram* MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc);
};