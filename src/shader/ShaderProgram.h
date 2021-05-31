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

	void SetUniformInt(const std::string& name, const int value) const;
	void SetUniformFloat(const std::string& name, const float value) const;
	void SetUniformVec3(const std::string& name, const glm::vec3& value) const;
	void SetUniformMat4(const std::string& name, const glm::mat4& value) const;
};


