#pragma once
#include <string>
#include <glm/glm.hpp>
#include "MaterialBase.h"
#include "../shader/ShaderProgram.h"


class FlatMaterial final : public MaterialBase {
private:
	const std::string colorName = "color";

public:
	FlatMaterial() = default;

	/// <summary>
	/// Constructor. Shader program is mandatory.
	/// Sets the color to the default (0,0,0).
	/// </summary>
	/// <param name="shaderProgram">Shader program</param>
	FlatMaterial(ShaderProgram& shaderProgram);

	/// <summary>
	/// Destructor.
	/// </summary>
	~FlatMaterial();

	/// <summary>
	/// Sets the flat color.
	/// </summary>
	/// <param name="color">Color (RGB)</param>
	void SetColor(const glm::vec3& color);
};

