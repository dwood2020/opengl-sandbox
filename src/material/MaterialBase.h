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

	/// <summary>
	/// Common uniforms.
	/// These uniforms are shared between different materials - storing a copy of them in each
	/// material instance makes no sense.
	/// These commonly used uniforms are: model matrix, view projection matrix, view pos.
	/// </summary>
	std::map<std::string, int> commonUniformLocations;	//TODO: Think about using enum for types

	std::map<std::string, Uniform> uniforms;

	std::vector<const Texture*> textures;

	int maxTextures;

	bool isAffectedByLight;


	MaterialBase() = default;

public:	
	/// <summary>
	/// Constructor. A  shader program is mandatory.	
	/// </summary>
	/// <param name="shaderProgram">Shader program</param>
	MaterialBase(ShaderProgram* shaderProgram);

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~MaterialBase();

	/// <summary>
	/// Sets a common uniform location.
	/// </summary>
	/// <param name="name">Uniform name</param>
	/// <param name="location">Uniform location</param>
	void SetCommonUniformLocation(const std::string& name, int location);

	/// <summary>
	/// Gets a common uniform location.
	/// </summary>
	/// <param name="name">Uniform name</param>
	/// <returns>Uniform location</returns>
	int GetCommonUniformLocation(const std::string& name) const;

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
	Uniform* GetUniform(const std::string& name);	

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
	ShaderProgram* GetShaderProgram(void);

	/// <summary>
	/// Sends ALL set uniforms to the shader program and retrieves + caches their uniform locations
	/// on the first send.
	/// NOTE: Common uniform locations are not used by this function.
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
