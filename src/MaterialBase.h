#pragma once
#include <map>
#include <string>
#include <vector>
#include "shader/ShaderProgram.h"
#include "Uniform.h"
#include "Texture.h"


/// <summary>
/// Material base class.
/// This class covers all the interaction with the shader program regarding materials.
/// It it shall be derived by every material type child class.
/// </summary>
class MaterialBase {
protected:
	ShaderProgram* shaderProgram;

	std::map<std::string, Uniform> uniforms;

	std::vector<Texture*> textures;
	
	int maxTextures;


	MaterialBase() = default;

public:	
	/// <summary>
	/// Constructor. A reference to a shader program is mandatory.
	/// </summary>
	/// <param name="shaderProgram">Shader program</param>
	MaterialBase(ShaderProgram& shaderProgram);

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~MaterialBase();

	/// <summary>
	/// Sets a uniform.
	/// </summary>
	/// <param name="name">Uniform name</param>
	/// <param name="uniform">Uniform object</param>
	void SetUniform(const std::string& name, Uniform& uniform);

	/// <summary>
	/// Gets a uniform object by name.
	/// </summary>
	/// <param name="name">Uniform name</param>
	/// <returns>Uniform object</returns>
	const Uniform* GetUniform(const std::string& name) const;


	void SetTexture(Texture& texture);

	/// <summary>
	/// Sends ALL set uniforms to the shader program and retrieves + caches their uniform locations
	/// on the first send.
	/// NOTE: Call this outside of the render loop.
	/// </summary>	
	void Prepare(void);

	/// <summary>
	/// "Binds" the material by binding all set textures and using the shader program.
	/// </summary>	
	void Bind(void) const;

	/// <summary>
	/// "Unbinds" the material by unbinding all textures.
	/// </summary>	
	void Unbind(void) const;

};
