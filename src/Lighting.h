#pragma once
#include <glm/glm.hpp>
#include "shader/ShaderProgram.h"


/// <summary>
/// This class holds all required information for the light settings.
/// KISS: Currently only one directional light source supported.
/// </summary>
class Lighting final {
private:
	glm::vec3 direction;
	glm::vec3 color;
	float ambient;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	Lighting();

	~Lighting();


	/// <summary>
	/// Sets the (directional) lights direction
	/// </summary>
	/// <param name="direction">light direction</param>
	void SetDirection(const glm::vec3& direction);


	/// <summary>
	/// Sets the light color.
	/// </summary>
	/// <param name="color">light color</param>
	void SetColor(const glm::vec3& color);


	/// <summary>
	/// Sets the ambient factor, e.g. the "strength" of the ambient light.
	/// This should be in the range within 0.0f- 1.0f
	/// </summary>
	/// <param name="ambient">ambient light factor</param>
	void SetAmbientFactor(float ambient);


	/// <summary>
	/// Sets all lighting uniforms in the given shader program.
	/// The shader program must contain the appropriate uniform declarations.
	/// </summary>
	/// <param name="shaderProg">Shader program to set the uniforms in</param>
	void SetUniforms(ShaderProgram* shaderProg) const;
};



