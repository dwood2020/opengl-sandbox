#include "Texture.h"
#include <stb/stb_image.h>
#include "glad/glad.h"

#include <iostream>

Texture::Texture(): id(0) { }


Texture::~Texture() { }


void Texture::Generate(GLsizei w, GLsizei h, GLenum format, unsigned char* data) {
	if (data == nullptr) {
		std::cout << "TEXTURE::GENERATE: Data array is null" << std::endl;
		return;
	}

	const GLint level = 0;

	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(id, level, (GLint)format, w, h, 0, format, GL_UNSIGNED_BYTE, data);

	const GLint paramWrap = GL_REPEAT;		// applied as wrapping in s and t direction
	const GLint paramFilter = GL_LINEAR;	// applied as min and max filter setting
	//NOTE: try GL_NEAREST as filter setting for minecraft style?

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paramWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paramWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, paramFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, paramFilter);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Bind(void) const {
	glActiveTexture(GL_TEXTURE0);	//TODO: move this when more than 1 texture is used
	glBindTexture(GL_TEXTURE_2D, id);
}






Texture Texture::GenerateFromFile(const std::string& filepath) {

	int w;
	int h;
	int nrChannels;
	const int desiredChannels = 0;

	unsigned char* data = stbi_load(filepath.c_str(), &w, &h, &nrChannels, desiredChannels);

	GLenum imageFormat = GetImageFormat(filepath);

	Texture obj;
	obj.Generate(w, h, imageFormat, data);

	stbi_image_free(data);

	return obj;
}



GLenum Texture::GetImageFormat(const std::string& filepath) {
	size_t posEnding = filepath.find_last_of('.');

	std::string ending = filepath.substr(posEnding + 1u);
	for (size_t i = 0; i < ending.size(); ++i) {
		ending[i] = std::tolower(ending[i]);
	}
	//TODO: catch exceptions here! (in case string is no ascii string etc...)

	if (ending.compare("png") == 0) {
		return GL_RGBA;
	}
	else if (ending.compare("jpg") == 0 || ending.compare("jpeg") == 0) {
		return GL_RGB;
	}	
	else {
		// assume no alphas by default
		//TODO: different image formats
		return GL_RGB;
	}

}
