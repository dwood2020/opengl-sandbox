#include "ShaderFactory.h"
#include "../glad/glad.h"


ShaderFactory::ShaderFactory() { }


ShaderFactory::~ShaderFactory() {
	for (ShaderProgram* ref : refs) {
		delete ref;
	}
}


ShaderProgram* ShaderFactory::MakeDefaultPhongShaderProgram(void) {	
	return MakeShaderProgram(Shader::ReadSourceFromFile(phongVertSourePath), Shader::ReadSourceFromFile(phongFragSourcePath));
}


ShaderProgram* ShaderFactory::MakeDefaultFlatShaderProgram(void) {	
	return MakeShaderProgram(Shader::ReadSourceFromFile(flatVertSourcePath), Shader::ReadSourceFromFile(flatFragSourcePath));
}


ShaderProgram* ShaderFactory::MakeShaderProgram(const std::string& vertSrc, const std::string& fragSrc) {

	Shader vertShader(vertSrc.c_str(), GL_VERTEX_SHADER);
	Shader fragShader(fragSrc.c_str(), GL_FRAGMENT_SHADER);

	//TODO: handle unsuccessful compilation or linking
	vertShader.CheckCompilationStatus();
	fragShader.CheckCompilationStatus();
		
	//std::shared_ptr<ShaderProgram> shaderProg = std::make_shared<ShaderProgram>(new ShaderProgram(vertShader, fragShader));

	ShaderProgram* shaderProg = new ShaderProgram(vertShader, fragShader);	
	if (!shaderProg->CheckLinkStatus()) {
		delete shaderProg;
		return nullptr;
	}

	refs.push_back(shaderProg);
	return shaderProg;
}

