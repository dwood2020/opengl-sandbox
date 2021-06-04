#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "MaterialBase.h"
#include "../shader/ShaderProgram.h"


/// <summary>
/// This class represents a Phong-model material.
/// </summary>
class PhongMaterial final : public MaterialBase {
private:
	const std::string diffuseName = "material.diffuseColor";
	const std::string specularName = "material.specularColor";
	const std::string shininessName = "material.shininess";
	const std::string hasDiffuseTextureName = "material.hasDiffuseTexture";
	const std::string useTexCoordsName = "useTexCoords";

	bool hasDiffuseTexture;		//NOTE: these booleans are actually unnecessary but are used to represent the same variables here as uniforms in the shader.
	bool hasSpecularTexture;


	PhongMaterial() = default;

public:
	/// <summary>
	/// Constructor. Shader program is mandatory.
	/// </summary>
	/// <param name="shaderProgram">Shader program</param>
	PhongMaterial(std::shared_ptr<ShaderProgram> shaderProgram);

	/// <summary>
	/// Destructor.
	/// </summary>
	~PhongMaterial();

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

};


