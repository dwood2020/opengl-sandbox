#pragma once
#include "glad/glad.h"
#include <string>


class Texture final {
public:
	GLuint id;

public:	
	Texture();
	~Texture();

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
	/// Binds this texture object as active texture
	/// </summary>	
	void Bind(void) const;
	
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

};
