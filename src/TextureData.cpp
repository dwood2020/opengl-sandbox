#include "TextureData.h"
#include <stb/stb_image.h>


TextureData::TextureData(): data(nullptr), width(0), height(0), nrChannels(0) { }


TextureData::~TextureData() {
	stbi_image_free(data);	
}


void TextureData::LoadFromFile(const std::string& filepath, bool flipVerticallyOnLoad) {
	stbi_set_flip_vertically_on_load(flipVerticallyOnLoad);

	const int desiredChannels = 0;
	data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, desiredChannels);
}


const unsigned char* TextureData::GetRaw(void) const {
	return data;
}


int TextureData::GetWidth(void) const {
	return width;
}


int TextureData::GetHeight(void) const {
	return height;
}


int TextureData::GetNrChannels(void) const {
	return nrChannels;
}
