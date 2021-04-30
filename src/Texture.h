#pragma once
#include "glad/glad.h"
#include <string>


class Texture final {
public:
	GLuint id;

public:	
	Texture();
	~Texture();

	void Generate(GLsizei w, GLsizei h, GLenum format, unsigned char* data);

	void Bind(void) const;
	
	static Texture GenerateFromFile(const std::string& filepath);

};
