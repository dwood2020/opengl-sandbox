#include "MaterialBase.h"


MaterialBase::MaterialBase(ShaderProgram& shaderProgram): shaderProgram(&shaderProgram), texture(nullptr) { }


MaterialBase::~MaterialBase() { }


void MaterialBase::SetUniform(const std::string& name, Uniform& uniform) {
	uniforms[name];
}


const Uniform* MaterialBase::GetUniform(const std::string& name) const {	
	auto it = uniforms.find(name);
	if (it != uniforms.end()) {
		return &it->second;
	}
	return nullptr;
}
