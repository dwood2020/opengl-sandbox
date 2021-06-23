#include "DynamicMesh.h"


DynamicMesh::DynamicMesh(): vao(0), vbo(0), useTexCoords(false), nrElements(0) {
	
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
				

		nrElements = static_cast<GLsizei>(verticesPosNormTex.size());
	}
	else {
		// do the same for a vertex buffer without tex coords
		glBufferData(GL_ARRAY_BUFFER, verticesPosNorm.size() * sizeof(VertexPosNorm), &verticesPosNorm[0].pos.x, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNorm), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosNorm), (void*)sizeof(VertexPosNorm::pos));		
		glEnableVertexAttribArray(1);

		nrElements = (GLsizei)verticesPosNorm.size();
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


