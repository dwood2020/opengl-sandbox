#include "Texture.h"
#include <stb/stb_image.h>


Texture::Texture(): id(0), w(0), h(0), format(0) { }


Texture::~Texture() { }


void Texture::Generate(unsigned char* data) {
	
}



unsigned char* Texture::LoadData(const std::string& filepath) {
	return nullptr;
}


GLenum Texture::GetImageFormat(const std::string& filepath) {
	size_t posEnding = filepath.find_last_of('.');

	std::string ending = filepath.substr(posEnding + 1u);
	for (size_t i = 0; i < ending.size(); ++i) {
		ending[i] = std::tolower(ending[i]);
	}
	//TODO: catch exceptions here! (in case string is no ascii string etc...)

	if (ending.compare("png")) {
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
