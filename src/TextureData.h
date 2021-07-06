#pragma once
#include <string>

/// <summary>
/// This class contains the raw image data handling.
/// It acts as an abstraction layer onto the stb_image library.
/// </summary>
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

	int GetNrChannels(void) const;
};

