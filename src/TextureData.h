#pragma once
#include <string>


class TextureData final {
private:
	unsigned char* data;
	int width;
	int height;
	int nrChannels;

public:
	TextureData();

	~TextureData();

	void LoadFromFile(const std::string& filepath);

	const unsigned char* GetRaw(void) const;

	int GetWidth(void) const;

	int GetHeight(void) const;
};

