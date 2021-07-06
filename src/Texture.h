#pragma once
#include "glad/glad.h"
#include <string>


class Texture final {
private:
	GLuint id;

public:	
	Texture();
	~Texture();

	/// <summary>
	/// Gets the OpenGL texture ID.
	/// </summary>	
	/// <returns>ID</returns>
	GLuint GetId(void) const;

	/// <summary>
	/// Generates an OpenGL texture.
	/// </summary>
	/// <param name="w">width in pixels</param>
	/// <param name="h">height in pixels</param>
	/// <param name="format">OpenGL texture format, with or without alpha channel (GL_RGB or GL_RGBA) </param>
	/// <param name="data">image data array</param>
	/// <param name="glTexFilter">OpenGL Texture filter option (GL_NEAREST or GL_LINEAR)</param>
	void Generate(GLsizei w, GLsizei h, GLenum format, unsigned char* data, GLint glTexFilter = GL_LINEAR);

	/// <summary>
	/// Binds this texture object as active texture.
	/// </summary>	
	/// <param name="texture">the texture unit to bind to, e.g. GL_TEXTURE0, GL_TEXTURE1,... (see glActiveTexture)</param>
	void Bind(GLenum texture = GL_TEXTURE0) const;
	
	/// <summary>
	/// Unbinds the currently active texture object.
	/// </summary>	
	static void Unbind(void);

	/// <summary>
	/// Loads and generates a Texture object from an image file (using stb_image library).
	/// </summary>
	/// <param name="filepath">File path</param>
	/// <param name="glTexFilter">OpenGL Texture filter option (GL_NEAREST or GL_LINEAR)</param>
	/// <returns>Texture object</returns>
	static Texture GenerateFromFile(const std::string& filepath, GLint glTexFilter = GL_LINEAR);

	/// <summary>
	/// Gets the maximum possible amount of textures to be set at once, which is the lower value of either 
	/// - the maximum number of textures which can be accessed by the fragment shader or
	/// - the total maximum number of textures which can be used.
	/// </summary>	
	/// <returns>Maximum number of textures possible</returns>
	static int GetMaxTextures(void);

};
