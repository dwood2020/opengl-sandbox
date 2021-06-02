#pragma once
#include <map>
#include <string>
#include "shader/ShaderProgram.h"
#include "Uniform.h"


class MaterialBase {
protected:
	ShaderProgram* shaderProgram;
	std::map<std::string, Uniform> uniforms;

public:
	MaterialBase() = default;

	MaterialBase(ShaderProgram& shaderProgram);

	virtual ~MaterialBase();




};
