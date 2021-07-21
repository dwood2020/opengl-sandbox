#include "MaterialBase.h"
#include <iostream>

MaterialBase::MaterialBase(ShaderProgram* shaderProgram): 
	shaderProgram(shaderProgram), isAffectedByLight(false), 
	mUniformLocation(-1), pvUniformLocation(-1), viewPosUniformLocation(-1) {
	//TODO: Next step: Parse all uniforms from shader and add to map.	

	maxTextures = Texture::GetMaxTextures();	
}


MaterialBase::~MaterialBase() {
	std::cout << "DEBUG: destroyed MaterialBase " << std::endl;
}


void MaterialBase::SetModelMatrixUniform(const glm::mat4& m) {
	if (mUniformLocation != -1) {
		shaderProgram->SetUniformMat4(mUniformLocation, m);
	}	
}


void MaterialBase::SetViewProjectionMatrixUniform(const glm::mat4& pv) {
	if (pvUniformLocation != -1) {
		shaderProgram->SetUniformMat4(pvUniformLocation, pv);
	}	
}


void MaterialBase::SetViewPosUniform(const glm::vec3& viewPos) {
	if (viewPosUniformLocation != -1) {
		shaderProgram->SetUniformVec3(viewPosUniformLocation, viewPos);
	}	
}


void MaterialBase::SetUniform(const std::string& name, const MaterialUniform& uniform) {
	uniforms[name] = uniform;
}


MaterialUniform* MaterialBase::GetUniform(const std::string& name) {	
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


ShaderProgram* MaterialBase::GetShaderProgram(void) {
	//NOTE: This does NOT make the unique_ptr release ownership. 
	//return shaderProgram.get();
	return shaderProgram;
}


void MaterialBase::Prepare(void) {
	shaderProgram->Use();

	// set all default common uniform locations
	//TODO: Save common uniform names globally/differently than hard coded
	if (mUniformLocation == -1) {
		mUniformLocation = shaderProgram->GetUniformLocation("M");
	}
	if (pvUniformLocation == -1) {
		pvUniformLocation = shaderProgram->GetUniformLocation("PV");
	}
	if (isAffectedByLight && viewPosUniformLocation == -1) {
		viewPosUniformLocation = shaderProgram->GetUniformLocation("viewPos");
	}

	// set all fixed uniforms
	for (auto it = uniforms.begin(); it != uniforms.end(); ++it) {
		if (it->second.GetLocation() == -1) {
			it->second.SetLocation(shaderProgram->GetUniformLocation(it->first));
		}

		switch (it->second.GetType()) {
		case MaterialUniformType::Int:
			shaderProgram->SetUniformInt(it->second.GetLocation(), it->second.GetInt());
			break;
		case MaterialUniformType::Float:
			shaderProgram->SetUniformFloat(it->second.GetLocation(), it->second.GetFloat());
			break;
		case MaterialUniformType::Vec3:
			shaderProgram->SetUniformVec3(it->second.GetLocation(), it->second.GetVec3());
			break;
		case MaterialUniformType::Vec4:
			shaderProgram->SetUniformVec4(it->second.GetLocation(), it->second.GetVec4());
			break;
		case MaterialUniformType::Mat4:
			shaderProgram->SetUniformMat4(it->second.GetLocation(), it->second.GetMat4());
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

	shaderProgram->Use();
}


void MaterialBase::Unbind(void) const {
	if (!textures.empty()) {
		Texture::Unbind();
	}

	// for clean architecture, this could be done: (or even packed into a static method within ShaderProgram class)
	// glUseProgram(0);
	// ... however, this is not necessary. So it is left out to improve performance.
}
