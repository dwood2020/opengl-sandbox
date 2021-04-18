#include "Shader.h"
#include <vector>
#include <iostream>


Shader::Shader(const char* src, GLenum glShaderType) {	

	//creates empty shader obj. Shader obj needs a shader source code attached.
	this->id = glCreateShader(glShaderType);
	
	glShaderSource(this->id, 1, &src, NULL);	//shader source is now copied to shader obj
	glCompileShader(this->id);	//(attempts to) compile the shader
}


Shader::~Shader() { }


bool Shader::CheckCompilationStatus(void) {
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		GLint infologLen;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLen);

		std::vector<GLchar> infolog(infologLen);
		glGetShaderInfoLog(id, infologLen, &infologLen, &infolog[0]);

		std::cout << "ERROR::SHADER::COMPILATION_STATUS:\n" << infolog.data() << std::endl;
	}
	return (bool)success;
}
