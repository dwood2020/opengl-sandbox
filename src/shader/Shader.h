#pragma once
#include <string>
#include "../glad/glad.h"


/// <summary>
/// This class represents a single OpenGL shader.
/// Note the difference between shader and shader program in OpenGL.
/// </summary>
class Shader {
public:
	unsigned int id;

public:
	/// <summary>
	/// Reads shader source code from a file.
	/// </summary>
	/// <param name="filepath">File path</param>
	/// <returns>File content</returns>
	static std::string ReadSourceFromFile(const std::string& filepath);

	/// <summary>
	/// Constructor. 
	/// </summary>
	/// <param name="src">Shader source code</param>
	/// <param name="glShaderType">OpenGL shader type: Vertex or fragment shader</param>
	Shader(const char* src, GLenum glShaderType);

	~Shader();

	/// <summary>
	/// Checks the shader compilation status.
	/// </summary>	
	/// <returns>True if compilation successful</returns>
	bool CheckCompilationStatus(void);

private:
	Shader() = default;

};


