#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "../shader/ShaderProgram.h"
#include "../Uniform.h"
#include "../Texture.h"


/// <summary>
/// Material base class.
/// This class covers all the interaction with the shader program regarding materials.
/// It it shall be derived by every material type child class.
/// </summary>
class MaterialBase {
protected:
	ShaderProgram* shaderProgram;
	//std::unique_ptr<ShaderProgram> shaderProgram;
	//std::shared_ptr<ShaderProgram> shaderProgram;

	std::map<std::string, Uniform> uniforms;

	std::vector<const Texture*> textures;
	
	int maxTextures;

	bool isAffectedByLight;


	MaterialBase() = default;

public:	
	/// <summary>
	/// Constructor. A  shader program is mandatory.
	/// NOTE: This transfers ownership of the shader program onto the material.
	/// </summary>
	/// <param name="shaderProgram">Shader program</param>
	MaterialBase(ShaderProgram* shaderProgram);

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~MaterialBase();

	/// <summary>
	/// Sets a uniform.
	/// </summary>
	/// <param name="name">Uniform name</param>
	/// <param name="uniform">Uniform object</param>
	void SetUniform(const std::string& name, const Uniform& uniform);

	/// <summary>
	/// Gets a uniform object by name.
	/// </summary>
	/// <param name="name">Uniform name</param>
	/// <returns>Uniform object</returns>
	const Uniform* GetUniform(const std::string& name) const;

	/// <summary>
	/// Adds a texture to the texture stack.
	/// This is possible until the maxTextures is reached.
	/// </summary>
	/// <param name="texture">Texture</param>
	void SetTexture(const Texture& texture);

	/// <summary>
	/// Sets this material to be affected by light. 
	/// </summary>
	/// <param name="isAffected">True if material is affected by light</param>
	void SetAffectedByLight(bool isAffected);

	/// <summary>
	/// Gets whether the material is affected by light.
	/// </summary>	
	/// <returns>True if material is affected by light</returns>
	bool GetAffectedByLight(void) const;

	/// <summary>
	/// Gets the associated Shader program.
	/// </summary>	
	/// <returns>Shader program</returns>
	const ShaderProgram* GetShaderProgram(void) const;

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
