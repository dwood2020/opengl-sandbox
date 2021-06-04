#pragma once
#include <memory>
#include <string>
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

public:
	ShaderFactory();
	~ShaderFactory();

	std::shared_ptr<ShaderProgram> MakeDefaultPhongShaderProgram(void) const;

	std::shared_ptr<ShaderProgram> MakeDefaultFlatShaderProgram(void) const;

private:
	const ShaderProgram* MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc) const;
};