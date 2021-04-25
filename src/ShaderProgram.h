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

	void SetUniformInt(const std::string& name, int value);
	void SetUniformFloat(const std::string& name, float value);
	void SetUniformMat4(const std::string& name, glm::mat4& value);
};


