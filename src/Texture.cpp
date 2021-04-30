#include "Texture.h"
#include <stb/stb_image.h>
#include "glad/glad.h"

#include <iostream>

Texture::Texture(): id(0) { }


Texture::~Texture() { }


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


void Texture::Bind(void) const {
	//glActiveTexture(GL_TEXTURE0);	//TODO: move this when more than 1 texture is used
	glBindTexture(GL_TEXTURE_2D, id);
}



Texture Texture::GenerateFromFile(const std::string& filepath, GLint glTexFilterParam) {

	int w;
	int h;
	int nrChannels;
	const int desiredChannels = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath.c_str(), &w, &h, &nrChannels, desiredChannels);

	GLenum imageFormat;
	if(nrChannels == 4) {
		imageFormat = GL_RGBA;
	}
	else {
		imageFormat = GL_RGB;
	}

	Texture obj;
	obj.Generate(w, h, imageFormat, data, glTexFilterParam);

	stbi_image_free(data);

	return obj;
}

