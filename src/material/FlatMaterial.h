#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "MaterialBase.h"
#include "../shader/ShaderProgram.h"


/// <summary>
/// This class represents a flat material.
/// Flat materials consist of a single "flat" color (RGBA).
/// It is also possible to use color vertices instead.
/// </summary>
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
	/// <param name="color">Color (RGBA)</param>
	void SetFlatColor(const glm::vec4& color);

	/// <summary>
	/// Enables the usage of color vertices in the shader.
	/// </summary>
	/// <param name="set">True to enable</param>
	void SetUseColorVertices(bool set);
};

