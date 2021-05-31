#pragma once
#include <glm/glm.hpp>
#include "shader/ShaderProgram.h"
#include "Texture.h"


/// <summary>
/// This class represents a simple Phong material.
/// </summary>
class Material {
protected:
	const ShaderProgram* shaderProg;

	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;

	bool hasDiffuseTexture;		//NOTE: these booleans are actually unnecessary but are used to represent the same variables here as uniforms in the shader.
	bool hasSpecularTexture;
	const Texture* diffuseTexture;
	const Texture* specularTexture;

	const int diffuseTextureIndex = 0;
	const int specularTextureIndex = 1;

private:
	Material() = default;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// /// <param name="shaderProg">Shader program to be used with the material</param>
	Material(const ShaderProgram& shaderProg);


	/// <summary>
	/// Destructor.
	/// </summary>	
	virtual ~Material();


	/// <summary>
	/// Sets the material's diffuse color.
	/// </summary>
	/// <param name="diffuse">Diffuse color</param>
	void SetDiffuseColor(const glm::vec3& diffuse);


	/// <summary>
	/// Sets the material's diffuse texture.
	/// </summary>
	/// <param name="diffuse">Diffuse texture</param>
	void SetDiffuseTexture(const Texture& diffuse);


	/// <summary>
	/// Sets the material's specular (reflection) color.
	/// </summary>
	/// <param name="specular">Specular color</param>
	void SetSpecularColor(const glm::vec3& specular);


	/// <summary>
	/// Sets the material's specular texture (reflection map)
	/// </summary>
	/// <param name="specular">Specular texture</param>
	void SetSpecularTexture(const Texture& specular);


	/// <summary>
	/// Sets the material's shininess parameter.
	/// (The higher this param. is, the "glossier"/"shinier" appears the material's reflection)
	/// Typical ranges are: 16 - 256, default: 32
	/// </summary>
	/// <param name="shininess">shininess parameter</param>
	void SetShininess(float shininess);


	/// <summary>
	/// Sets all material uniforms in the given shader program.
	/// The shader program must contain the appropriate uniform declarations.
	/// </summary>	
	void SetUniforms(void);


	/// <summary>
	/// Binds the material's textures if it has any.
	/// </summary>	
	void BindTextures(void) const;

};

