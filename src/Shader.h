#pragma once
#include <string>
#include "glad/glad.h"


class Shader {
public:
	unsigned int id;

public:
	static std::string ReadSourceFromFile(const std::string& filepath);

	Shader(const char* src, GLenum glShaderType);
	~Shader();

	bool CheckCompilationStatus(void);

private:
	Shader() = default;

};


