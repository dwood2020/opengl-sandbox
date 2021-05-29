#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"


/// <summary>
/// This class represents a simple Phong material.
/// </summary>
class Material {
protected:
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	Material();

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
	/// Sets the material's specular (reflection) color.
	/// </summary>
	/// <param name="specular">Specular color</param>
	void SetSpecularColor(const glm::vec3& specular);

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
	/// <param name="shaderProg">Shader program to set the uniforms in</param>
	void SetUniforms(ShaderProgram& shaderProg) const;
};

