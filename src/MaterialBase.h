#pragma once
#include <map>
#include <string>
#include "Uniform.h"


class MaterialBase {
protected:
	std::map<std::string, Uniform> uniforms;

public:
	MaterialBase() = default;

	virtual ~MaterialBase();


};
