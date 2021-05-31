#include "ShaderFactory.h"


ShaderFactory::ShaderFactory() { }


ShaderFactory::~ShaderFactory() { }


std::unique_ptr<ShaderProgram> ShaderFactory::MakePhongShaderProgram(void) const {
	
	
	return std::unique_ptr<ShaderProgram>();
}

