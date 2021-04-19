#include "Mesh.h"
#include <cstddef>


Mesh::Mesh(std::vector<glm::vec3>& vertices) : Mesh() {
	verticesPosition = vertices;
}


Mesh::Mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices):
	Mesh() { 
		
	verticesPosition = vertices;	
	this->indices = indices;
}


Mesh::Mesh() : vao(0), vbo(0), ebo(0), glMode(GL_POINTS), nrElements(0) { }


Mesh::~Mesh() { }


void Mesh::SetMode(GLenum glMode) {
	this->glMode = glMode;
}


void Mesh::Prepare(void) {
	size_t dataSize = verticesPosition.size() * 3 + verticesTexCoord.size() * 2 + verticesNormal.size() * 3;
	
	std::vector<float> data;
	data.reserve(dataSize);

	if (!indices.empty()) {
		nrElements = (GLsizei)indices.size();
	}
	else {
		nrElements = (GLsizei)verticesPosition.size();
	}
	

	for (unsigned int i = 0; i < verticesPosition.size(); i++) {
		data.push_back(verticesPosition[i].x);
		data.push_back(verticesPosition[i].y);
		data.push_back(verticesPosition[i].z);

		if (!verticesTexCoord.empty()) {
			data.push_back(verticesTexCoord[i].x);
			data.push_back(verticesTexCoord[i].y);
		}

		if (!verticesNormal.empty()) {
			data.push_back(verticesNormal[i].x);
			data.push_back(verticesNormal[i].y);
			data.push_back(verticesNormal[i].z);
		}
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	if (!indices.empty()) {
		glGenBuffers(1, &ebo);
	}

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW);

	if (!indices.empty()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
	}
	
	//CAUTION here with stride and offset/pointer
	GLsizei stride;
	stride = 3 * sizeof(float);

	if (!verticesTexCoord.empty()) {
		stride += 2 * sizeof(float);
	}
	if (!verticesNormal.empty()) {
		stride += 3 * sizeof(float);
	}

	GLsizei offset;
	offset = 0;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(0);
	offset += 3 * sizeof(float);

	if (!verticesTexCoord.empty()) {
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(1);
		offset += 2 * sizeof(float);
	}

	if (!verticesNormal.empty()) {
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(2);
		offset += 3 * sizeof(float);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	verticesPosition.clear();
	verticesTexCoord.clear();
	verticesNormal.clear();
	indices.clear();
}


void Mesh::Draw(void) {
	glBindVertexArray(vao);
	if (ebo == 0) {
		glDrawArrays(glMode, 0, nrElements);
	}
	else {
		glDrawElements(glMode, nrElements, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}