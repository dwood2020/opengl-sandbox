#include "ShaderFactory.h"
#include "../glad/glad.h"


ShaderFactory::ShaderFactory() { }


ShaderFactory::~ShaderFactory() { }


ShaderProgram ShaderFactory::MakeDefaultPhongShaderProgram(void) const {
	return MakeShaderProgram(Shader::ReadSourceFromFile(phongVertSourePath), Shader::ReadSourceFromFile(phongFragSourcePath));
}


ShaderProgram ShaderFactory::MakeDefaultFlatShaderProgram(void) const {
	return MakeShaderProgram(Shader::ReadSourceFromFile(flatVertSourcePath), Shader::ReadSourceFromFile(flatFragSourcePath));
}


ShaderProgram ShaderFactory::MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc) const {

	Shader vertShader(vertSrc.c_str(), GL_VERTEX_SHADER);
	Shader fragShader(fragSrc.c_str(), GL_FRAGMENT_SHADER);

	//TODO: handle unsuccessful compilation or linking
	vertShader.CheckCompilationStatus();
	fragShader.CheckCompilationStatus();

	ShaderProgram shaderProg(vertShader, fragShader);
	shaderProg.CheckLinkStatus();

	return shaderProg;
}

