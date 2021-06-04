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

	/// <summary>
	/// Makes a default phong model-based shader program.
	/// </summary>	
	/// <returns>Shader program</returns>
	ShaderProgram* MakeDefaultPhongShaderProgram(void);

	/// <summary>
	/// Makes a default flat shader program.	
	/// </summary>	
	/// <returns>Shader program</returns>
	ShaderProgram* MakeDefaultFlatShaderProgram(void);

private:
	/// <summary>
	/// Handles all the work to make a shader program.
	/// </summary>
	/// <param name="vertSrc">Vertex shader source</param>
	/// <param name="fragSrc">Fragment shader source</param>
	/// <returns></returns>
	ShaderProgram* MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc);
};