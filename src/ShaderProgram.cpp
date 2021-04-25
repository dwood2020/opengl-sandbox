#include "ShaderProgram.h"
#include "glad/glad.h"
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


void ShaderProgram::SetUniformInt(const std::string& name, int value) {
	int uniformLoc = glGetUniformLocation(id, name.c_str());
	glUniform1i(uniformLoc, value);
}


void ShaderProgram::SetUniformFloat(const std::string& name, float value) {
	int uniformLoc = glGetUniformLocation(id, name.c_str());
	glUniform1f(uniformLoc, value);
}


void ShaderProgram::SetUniformMat4(const std::string& name, glm::mat4& value) {
	int uniformLoc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &value[0][0]);
}
