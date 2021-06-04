#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "MaterialBase.h"
#include "../shader/ShaderProgram.h"


class FlatMaterial final : public MaterialBase {
private:
	const std::string colorName = "color";
	const std::string hasTextureVerticesName = "useColorVertices";

	bool useColorVertices;

public:
	FlatMaterial() = default;

	/// <summary>
	/// Constructor. Shader program is mandatory.
	/// Sets the color to the default (0,0,0).
	/// </summary>
	/// <param name="shaderProgram">Shader program</param>
	FlatMaterial(ShaderProgram* shaderProgram);

	/// <summary>
	/// Destructor.
	/// </summary>
	~FlatMaterial();

	/// <summary>
	/// Sets the flat color.
	/// </summary>
	/// <param name="color">Color (RGB)</param>
	void SetFlatColor(const glm::vec3& color);

	/// <summary>
	/// Enables the usage of color vertices in the shader.
	/// </summary>
	/// <param name="set">True to enable</param>
	void SetUseColorVertices(bool set);
};

