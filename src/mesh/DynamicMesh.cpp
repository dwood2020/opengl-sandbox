#include "DynamicMesh.h"
#include <string>
#include <iostream>


DynamicMesh::DynamicMesh(): vao(0), vbo(0), ebo(0), useNormals(false), useTexCoords(false), isInstanced(false), nrElements(0) {	}


DynamicMesh::~DynamicMesh() { }


std::vector<VertexPos>& DynamicMesh::GetVerticesPos(void) {
	return verticesPos;
}


std::vector<VertexPosNorm>& DynamicMesh::GetVerticesPosNorm(void) {
	return verticesPosNorm;
}


std::vector<VertexPosNormTex>& DynamicMesh::GetVerticesPosNormTex(void) {
	return verticesPosNormTex;
}


std::vector<GLuint>& DynamicMesh::GetIndices(void) {
	return indices;
}


void DynamicMesh::SetUseNormals(bool useNormals) {
	this->useNormals = useNormals;
}


void DynamicMesh::SetUseTexCoords(bool useTexCoords) {
	this->useTexCoords = useTexCoords;
}


void DynamicMesh::SetIsInstanced(bool isInstanced) {
	this->isInstanced = isInstanced;
}


void DynamicMesh::Prepare(void) {
	
	if (!CheckDataConsistency()) {
		std::cout << "DynamicMesh::Prepare: Data discrepancy" << std::endl;
	}
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	if (isInstanced) {
		glGenBuffers(1, &ebo);
	}

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (isInstanced) {		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	}

	if (useNormals && useTexCoords) {
		// allocate the buffer data
		glBufferData(GL_ARRAY_BUFFER, verticesPosNormTex.size() * sizeof(VertexPosNormTex), &verticesPosNormTex[0].pos.x, GL_STATIC_DRAW);

		// set up position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), (void*)0);
		glEnableVertexAttribArray(0);

		// set up normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), (void*)sizeof(VertexPosNorm::pos));
		glEnableVertexAttribArray(1);

		// set up tex coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), (void*)(sizeof(VertexPosNorm::pos) + sizeof(VertexPosNorm::norm)));
		glEnableVertexAttribArray(2);

		if (isInstanced) {
			nrElements = (GLsizei)indices.size();
		}
		else {
			nrElements = static_cast<GLsizei>(verticesPosNormTex.size());
		}
		
	}
	else if (useNormals) {
		// do the same for a vertex buffer without tex coords
		glBufferData(GL_ARRAY_BUFFER, verticesPosNorm.size() * sizeof(VertexPosNorm), &verticesPosNorm[0].pos.x, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNorm), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNorm), (void*)sizeof(VertexPosNorm::pos));
		glEnableVertexAttribArray(1);

		if (isInstanced) {
			nrElements = (GLsizei)indices.size();
		}
		else {
			nrElements = (GLsizei)verticesPosNorm.size();
		}
		
	}
	else {
		// do the same for vertex buffer without tex coords and normals
		glBufferData(GL_ARRAY_BUFFER, verticesPos.size() * sizeof(VertexPos), &verticesPos[0].pos.x, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPos), (void*)0);
		glEnableVertexAttribArray(0);

		if (isInstanced) {
			nrElements = (GLsizei)indices.size();
		}
		else {
			nrElements = (GLsizei)verticesPos.size();
		}
		
	}

	// unbind all
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void DynamicMesh::Draw(void) {
	if (isInstanced) {
		glDrawElements(glMode, nrElements, GL_UNSIGNED_INT, 0);
	}
	else {
		glBindVertexArray(vao);
		glDrawArrays(glMode, 0, nrElements);
	}
	
	//TODO: indexed rendering
}


void DynamicMesh::Update(void) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	if (useNormals && useTexCoords) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexPosNormTex) * verticesPosNormTex.size(), &verticesPosNormTex[0].pos.x);
	}
	else if (useNormals) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexPosNorm) * verticesPosNorm.size(), &verticesPosNorm[0].pos.x);
	}
	else {
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexPos) * verticesPos.size(), &verticesPos[0].pos.x);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


bool DynamicMesh::CheckDataConsistency(void) {
	// multiple if checks for enhanced code readability
	if (useNormals && useTexCoords && verticesPosNormTex.empty()) {
		return false;
	}
	else if (useNormals && !useTexCoords && verticesPosNorm.empty()) {
		return false;
	}
	else if (!useNormals && !useTexCoords && verticesPos.empty()) {
		return false;
	}
	else if (isInstanced && indices.empty()) {
		return false;
	}
	
	return true;
}


