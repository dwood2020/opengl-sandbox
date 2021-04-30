#pragma once
#include "glad/glad.h"
#include <string>


class Texture final {
public:
	GLuint id;

protected:
	GLuint w;
	GLuint h;
	GLenum format;

public:	
	Texture();
	~Texture();

	void Generate(unsigned char* data);

	static unsigned char* LoadData(const std::string& filepath);

private:
	static GLenum GetImageFormat(const std::string& filepath);

};
