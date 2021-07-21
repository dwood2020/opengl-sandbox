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


void ShaderProgram::Use(void) const {
	glUseProgram(id);
}


int ShaderProgram::GetUniformLocation(const std::string& name) const {
	return glGetUniformLocation(id, name.c_str());;
}


void ShaderProgram::SetUniformInt(int location, const int value) const {	
	glUniform1i(location, value);
}


void ShaderProgram::SetUniformFloat(int location, const float value) const {	
	glUniform1f(location, value);
}


void ShaderProgram::SetUniformVec3(int location, const glm::vec3& value) const {	
	glUniform3fv(location, 1, &value[0]);
}


void ShaderProgram::SetUniformVec4(int location, const glm::vec4& value) const {
	glUniform4fv(location, 1, &value[0]);
}


void ShaderProgram::SetUniformMat4(int location, const glm::mat4& value) const {	
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
