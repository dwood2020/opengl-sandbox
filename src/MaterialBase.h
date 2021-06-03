#pragma once
#include <map>
#include <string>
#include <vector>
#include "shader/ShaderProgram.h"
#include "Uniform.h"
#include "Texture.h"

//TODO: Add texture setter + check if max number of textures are set
// check here to retrieve this number: https://gamedev.stackexchange.com/questions/30043/how-many-textures-can-usually-i-bind-at-once

class MaterialBase {
protected:
	ShaderProgram* shaderProgram;

	std::map<std::string, Uniform> uniforms;

	std::vector<Texture*> textures;


	MaterialBase() = default;

public:	
	MaterialBase(ShaderProgram& shaderProgram);

	virtual ~MaterialBase();


	void SetUniform(const std::string& name, Uniform& uniform);


	const Uniform* GetUniform(const std::string& name) const;


	void Prepare(void);


	void Bind(void) const;


	void Unbind(void) const;

};
