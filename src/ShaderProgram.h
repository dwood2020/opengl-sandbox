#pragma once
#include "Shader.h"


class ShaderProgram {
public:
	unsigned int id;

public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();

	bool CheckLinkStatus(void);
	void Use(void);
};


