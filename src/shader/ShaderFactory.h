#pragma once
#include <memory>
#include <string>
#include <vector>
#include "ShaderProgram.h"


/// <summary>
/// This class handles shader construction and compilation.
/// It knows default shaders.
/// 
/// NOTE: Ownership of shader programs is currently NOT transferred.
/// </summary>
class ShaderFactory final {
private:
	const std::string phongVertSourePath = "res/phong_material_vert.glsl";
	const std::string phongFragSourcePath = "res/phong_material_frag.glsl";

	const std::string flatVertSourcePath = "res/flat_material_vert.glsl";
	const std::string flatFragSourcePath = "res/flat_material_frag.glsl";

	// this is a quick fix.
	//TODO: Rework this entire ownership system!
	std::vector<ShaderProgram*> refs;

public:
	ShaderFactory();
	~ShaderFactory();

	ShaderProgram* MakeDefaultPhongShaderProgram(void);

	ShaderProgram* MakeDefaultFlatShaderProgram(void);

private:
	ShaderProgram* MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc);
};