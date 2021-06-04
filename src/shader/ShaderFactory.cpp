#include "ShaderFactory.h"
#include "../glad/glad.h"


ShaderFactory::ShaderFactory() { }


ShaderFactory::~ShaderFactory() { }


std::shared_ptr<ShaderProgram> ShaderFactory::MakeDefaultPhongShaderProgram(void) const {
	return std::make_shared<ShaderProgram>(MakeShaderProgram(Shader::ReadSourceFromFile(phongVertSourePath), Shader::ReadSourceFromFile(phongFragSourcePath)));
}


std::shared_ptr<ShaderProgram> ShaderFactory::MakeDefaultFlatShaderProgram(void) const {
	return std::make_shared<ShaderProgram>(MakeShaderProgram(Shader::ReadSourceFromFile(flatVertSourcePath), Shader::ReadSourceFromFile(flatFragSourcePath)));
}


const ShaderProgram* ShaderFactory::MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc) const {

	Shader vertShader(vertSrc.c_str(), GL_VERTEX_SHADER);
	Shader fragShader(fragSrc.c_str(), GL_FRAGMENT_SHADER);

	//TODO: handle unsuccessful compilation or linking
	vertShader.CheckCompilationStatus();
	fragShader.CheckCompilationStatus();
		
	//std::shared_ptr<ShaderProgram> shaderProg = std::make_shared<ShaderProgram>(new ShaderProgram(vertShader, fragShader));

	ShaderProgram* shaderProg = new ShaderProgram(vertShader, fragShader);	
	shaderProg->CheckLinkStatus();

	return shaderProg;
}

