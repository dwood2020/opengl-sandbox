#include "ShaderProgram.h"
#include "../glad/glad.h"
#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader) {
	//create program obj
	id = glCreateProgram();

	// link shaders
	glAttachShader(id, vertexShader.id);
	glAttachShader(id, fragmentShader.id);
	glLinkProgram(id);
}


ShaderProgram::~ShaderProgram() {
	//installs program obj as part of current rendering state
	glDeleteProgram(id);
}


bool ShaderProgram::CheckLinkStatus(void) {
	GLint success = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (success != GL_TRUE) {
		GLint infologLen;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLen);

		std::vector<GLchar> infolog(infologLen);
		glGetShaderInfoLog(id, infologLen, &infologLen, &infolog[0]);

		std::cout << "ERROR::SHADERPROGRAM::LINK_STATUS:\n" << infolog.data() << std::endl;
	}
	return (bool)success;
}


void ShaderProgram::Use(void) {
	glUseProgram(id);
}

//TODO: (lazily?) save the uniform locations in map and look up to gather efficiency
void ShaderProgram::SetUniformInt(const std::string& name, const int value) const {
	int uniformLoc = glGetUniformLocation(id, name.c_str());
	glUniform1i(uniformLoc, value);
}


void ShaderProgram::SetUniformFloat(const std::string& name, const float value) const {
	int uniformLoc = glGetUniformLocation(id, name.c_str());
	glUniform1f(uniformLoc, value);
}


void ShaderProgram::SetUniformVec3(const std::string& name, const glm::vec3& value) const {
	int uniformLoc = glGetUniformLocation(id, name.c_str());
	glUniform3fv(uniformLoc, 1, &value[0]);
}


void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& value) const {
	int uniformLoc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &value[0][0]);
}
