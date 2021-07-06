#include "Texture.h"
#include <stb/stb_image.h>
#include "glad/glad.h"
#include <algorithm>
#include "TextureData.h"

#include <iostream>

Texture::Texture(): id(0) { }


Texture::~Texture() { }

GLuint Texture::GetId(void) const {
	return id;
}


void Texture::Generate(GLsizei w, GLsizei h, GLenum format, unsigned char* data, GLint glTexFilterParam) {
	if (data == nullptr) {
		std::cout << "TEXTURE::GENERATE: Data array is null" << std::endl;
		return;
	}

	const GLint level = 0;

	const GLint paramWrap = GL_REPEAT;		// applied as wrapping in s and t direction	
	//NOTE: glTexFilterParam applied as min and max filter setting
	//NOTE: use GL_NEAREST as filter setting for minecraft style

	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paramWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paramWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glTexFilterParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glTexFilterParam);

	glTexImage2D(GL_TEXTURE_2D, level, (GLint)format, w, h, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Bind(GLenum texture) const {
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, id);
}


void Texture::Unbind(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
}



Texture Texture::GenerateFromFile(const std::string& filepath, GLint glTexFilterParam) {

	TextureData texData;
	texData.LoadFromFile(filepath);

	GLenum imageFormat;
	if (texData.GetNrChannels() == 4) {
		imageFormat = GL_RGBA;
	}
	else {
		imageFormat = GL_RGB;
	}

	Texture obj;
	obj.Generate(texData.GetWidth(), texData.GetHeight(), imageFormat, const_cast<unsigned char*>(texData.GetRaw()), glTexFilterParam);

	return obj;
}


int Texture::GetMaxTextures(void) {
	int maxTexturesInFragShader;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTexturesInFragShader);

	return std::min(maxTexturesInFragShader, GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
}

