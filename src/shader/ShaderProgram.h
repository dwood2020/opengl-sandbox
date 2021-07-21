#pragma once
#include "Shader.h"
#include <glm/glm.hpp>


class ShaderProgram {
public:
	unsigned int id;

public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();

	bool CheckLinkStatus(void);
	void Use(void) const;

	int GetUniformLocation(const std::string& name) const;

	void SetUniformInt(int location, const int value) const;

	void SetUniformFloat(int location, const float value) const;

	void SetUniformVec3(int location, const glm::vec3& value) const;

	void SetUniformVec4(int location, const glm::vec4& value) const;

	void SetUniformMat4(int location, const glm::mat4& value) const;
};


