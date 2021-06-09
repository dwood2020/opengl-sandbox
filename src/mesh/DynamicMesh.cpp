#include "DynamicMesh.h"
#include "../glad/glad.h"


DynamicMesh::DynamicMesh(): vao(0), vbo(0), useTexCoords(false) {
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
}


DynamicMesh::~DynamicMesh() { }


void DynamicMesh::SetUseTexCoords(bool useTexCoords) {
	this->useTexCoords = useTexCoords;
}


void DynamicMesh::Prepare(void) {
	if (useTexCoords && verticesPosNormTex.size() == 0 || !useTexCoords && verticesPosNorm.size() == 0) {
		return;
	}

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (useTexCoords) {
		glBufferData(GL_ARRAY_BUFFER, verticesPosNormTex.size() * sizeof(VertexPosNormTex), &verticesPosNormTex.front(), GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, verticesPosNorm.size() * sizeof(VertexPosNorm), &verticesPosNorm.front(), GL_STATIC_DRAW);
	}

	//TODO continue here
	
}


void DynamicMesh::Draw(void) { }


