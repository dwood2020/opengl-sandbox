#pragma once
#include <string>


/// <summary>
/// This class contains the raw image data handling.
/// It acts as an abstraction layer onto the stb_image library and is independent from
/// any OpenGL specific code.
/// </summary>
class TextureData final {
private:
	unsigned char* data;
	int width;
	int height;
	int nrChannels;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	TextureData();

	~TextureData();

	/// <summary>
	/// Load texture data from an image file.
	/// </summary>
	/// <param name="filepath">File path</param>
	/// <param name="flipVerticallyOnLoad">See stb_image docs</param>
	void LoadFromFile(const std::string& filepath, bool flipVerticallyOnLoad = true);

	/// <summary>
	/// Get the raw image data.
	/// </summary>
	/// <returns>Raw image data</returns>
	const unsigned char* GetRaw(void) const;

	/// <summary>
	/// Get the texture width.
	/// </summary>
	/// <returns>Texture width</returns>
	int GetWidth(void) const;

	/// <summary>
	/// Get the texture height.
	/// </summary>
	/// <returns>Texture height</returns>
	int GetHeight(void) const;

	/// <summary>
	/// Get the number of color channels.
	/// </summary>
	/// <returns>Number of channels</returns>
	int GetNrChannels(void) const;
};

