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
	void Use(void);

	void SetUniformInt(const std::string& name, const int value);
	void SetUniformFloat(const std::string& name, const float value);
	void SetUniformVec3(const std::string& name, const glm::vec3& value);
	void SetUniformMat4(const std::string& name, const glm::mat4& value);
};


