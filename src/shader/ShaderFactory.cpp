#include "ShaderFactory.h"
#include "../glad/glad.h"


ShaderFactory::ShaderFactory() { }


ShaderFactory::~ShaderFactory() { }


std::unique_ptr<ShaderProgram> ShaderFactory::MakeDefaultPhongShaderProgram(void) const {
	return MakeShaderProgram(Shader::ReadSourceFromFile(phongVertSourePath), Shader::ReadSourceFromFile(phongFragSourcePath));
}


std::unique_ptr<ShaderProgram> ShaderFactory::MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc) const {

	Shader vertShader(vertSrc.c_str(), GL_VERTEX_SHADER);
	Shader fragShader(fragSrc.c_str(), GL_FRAGMENT_SHADER);

	//TODO: handle unsuccessful compilation or linking
	vertShader.CheckCompilationStatus();
	fragShader.CheckCompilationStatus();

	auto shaderProg = std::unique_ptr<ShaderProgram>(new ShaderProgram(vertShader, fragShader));
	shaderProg->CheckLinkStatus();

	return shaderProg;
}

