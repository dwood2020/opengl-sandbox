#include "MaterialBase.h"
#include <utility>


MaterialBase::MaterialBase(ShaderProgram shaderProgram): shaderProgram(shaderProgram) {
	//TODO: Next step: Parse all uniforms from shader and add to map.

	//NOTE: The material shall "own" the shader program.
	// This is currently done by simply copying-by-value.

	maxTextures = Texture::GetMaxTextures();
	isAffectedByLight = false;
}


MaterialBase::~MaterialBase() { }


void MaterialBase::SetUniform(const std::string& name, const Uniform& uniform) {
	uniforms[name] = uniform;
}


const Uniform* MaterialBase::GetUniform(const std::string& name) const {	
	auto it = uniforms.find(name);
	if (it != uniforms.end()) {
		return &it->second;
	}
	return nullptr;
}


void MaterialBase::SetTexture(const Texture& texture) {
	//TODO: Check this, if storing pointers is optimal or should be changed to store the entire object.
	if ((int)textures.size() < maxTextures - 1) {
		textures.push_back(&texture);
	}
	else {
		//TODO: ASSERT
	}
}


void MaterialBase::SetAffectedByLight(bool isAffected) {
	isAffectedByLight = isAffected;
}


bool MaterialBase::GetAffectedByLight(void) const {
	return isAffectedByLight;
}


const ShaderProgram* MaterialBase::GetShaderProgram(void) const {
	//NOTE: This does NOT make the unique_ptr release ownership. 
	//return shaderProgram.get();
	return &shaderProgram;
}


void MaterialBase::Prepare(void) {
	shaderProgram.Use();

	for (auto it = uniforms.begin(); it != uniforms.end(); ++it) {
		if (it->second.GetLocation() == -1) {
			it->second.SetLocation(shaderProgram.GetUniformLocation(it->first));
		}

		switch (it->second.GetType()) {
		case UniformType::Int:
			shaderProgram.SetUniformInt(it->second.GetLocation(), it->second.GetInt());
			break;
		case UniformType::Float:
			shaderProgram.SetUniformFloat(it->second.GetLocation(), it->second.GetFloat());
			break;
		case UniformType::Vec3:
			shaderProgram.SetUniformVec3(it->second.GetLocation(), it->second.GetVec3());
			break;
		case UniformType::Mat4:
			shaderProgram.SetUniformMat4(it->second.GetLocation(), it->second.GetMat4());
			break;
		default:
			break;
		}
	}
}


void MaterialBase::Bind(void) const {
	if (!textures.empty()) {
		for (unsigned int i = 0; i < textures.size(); i++) {
			textures[i]->Bind(GL_TEXTURE0 + i);
		}
	}

	shaderProgram.Use();
}


void MaterialBase::Unbind(void) const {
	if (!textures.empty()) {
		Texture::Unbind();
	}

	// for clean architecture, this could be done: (or even packed into a static method within ShaderProgram class)
	// glUseProgram(0);
	// ... however, this is not necessary. So it is left out to improve performance.
}
