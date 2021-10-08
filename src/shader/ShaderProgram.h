#pragma once
#include "Shader.h"
#include <glm/glm.hpp>


/// <summary>
/// This class represents an OpenGL shader program.
/// Note the difference between shader and shader program in OpenGL.
/// </summary>
class ShaderProgram {
public:
	unsigned int id;

public:
	/// <summary>
	/// Constructor. 
	/// </summary>
	/// <param name="vertexShader">Vertex shader</param>
	/// <param name="fragmentShader">Fragment shader</param>
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	
	~ShaderProgram();


	/// <summary>
	/// Checks the shader program link status.
	/// </summary>
	/// <returns>True if successful</returns>
	bool CheckLinkStatus(void);


	/// <summary>
	/// Use the shader program. This is intended to be only called by the renderer.
	/// </summary>
	void Use(void) const;


	/// <summary>
	/// Get a uniform location by its name.
	/// </summary>
	/// <param name="name">Uniform name</param>
	/// <returns>Uniform location</returns>
	int GetUniformLocation(const std::string& name) const;


	/// <summary>
	/// Sets an int uniform.
	/// </summary>
	/// <param name="location">Uniform location</param>
	/// <param name="value">Value</param>
	void SetUniformInt(int location, const int value) const;


	/// <summary>
	/// Sets a float uniform.
	/// </summary>
	/// <param name="location">Uniform location</param>
	/// <param name="value">Value</param>
	void SetUniformFloat(int location, const float value) const;


	/// <summary>
	/// Sets a vec3 uniform.
	/// </summary>
	/// <param name="location">Uniform location</param>
	/// <param name="value">Value</param>
	void SetUniformVec3(int location, const glm::vec3& value) const;


	/// <summary>
	/// Sets a vec4 uniform.
	/// </summary>
	/// <param name="location">Uniform location</param>
	/// <param name="value">Value</param>
	void SetUniformVec4(int location, const glm::vec4& value) const;


	/// <summary>
	/// Sets a mat4 (4x4) uniform.
	/// </summary>
	/// <param name="location">Uniform location</param>
	/// <param name="value">Value</param>
	void SetUniformMat4(int location, const glm::mat4& value) const;
};


