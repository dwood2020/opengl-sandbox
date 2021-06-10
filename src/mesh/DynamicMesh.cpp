#include "DynamicMesh.h"


DynamicMesh::DynamicMesh(): vao(0), vbo(0), useTexCoords(false) {
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
}


DynamicMesh::~DynamicMesh() { }


std::vector<VertexPosNorm>& DynamicMesh::GetVerticesPosNorm(void) {
	return verticesPosNorm;
}


std::vector<VertexPosNormTex>& DynamicMesh::GetVerticesPosNormTex(void) {
	return verticesPosNormTex;
}


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
		// allocate the buffer data
		glBufferData(GL_ARRAY_BUFFER, verticesPosNormTex.size() * sizeof(VertexPosNormTex), &verticesPosNormTex.front(), GL_STATIC_DRAW);

		// set up position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), (float*)&verticesPosNormTex[0].pos);

		// set up normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), (float*)&verticesPosNormTex[0].norm);

		// set up tex coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), (float*)&verticesPosNormTex[0].tex);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		nrElements = verticesPosNormTex.size();
	}
	else {
		// do the same for a vertex buffer without tex coords
		glBufferData(GL_ARRAY_BUFFER, verticesPosNorm.size() * sizeof(VertexPosNorm), &verticesPosNorm.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNorm), (float*)&verticesPosNorm[0].pos);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNorm), (float*)&verticesPosNorm[0].norm);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		nrElements = verticesPosNorm.size();
	}

	// unbind all
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void DynamicMesh::Draw(void) {
	glBindVertexArray(vao);
	glDrawArrays(glMode, 0, nrElements);
	//TODO: indexed rendering
}


