#pragma once
#include <map>
#include <string>
#include "shader/ShaderProgram.h"
#include "Uniform.h"
#include "Texture.h"


class MaterialBase {
protected:
	ShaderProgram* shaderProgram;

	std::map<std::string, Uniform> uniforms;

	Texture* texture;


	MaterialBase() = default;

public:	
	MaterialBase(ShaderProgram& shaderProgram);

	virtual ~MaterialBase();


	void SetUniform(const std::string& name, Uniform& uniform);


	const Uniform* GetUniform(const std::string& name) const;

};
