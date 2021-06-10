#include "StaticMesh.h"
#include <cstddef>
#include <algorithm>

#include <iostream>


StaticMesh::StaticMesh() : vao(0), vbo(0), ebo(0), nrElements(0) { }


StaticMesh::~StaticMesh() { }


void StaticMesh::SetPositionVertices(std::vector<glm::vec3>& vertices) {
	verticesPosition = vertices;
}


void StaticMesh::SetNormalVertices(std::vector<glm::vec3>& normals) {
	verticesNormal = normals;
}


void StaticMesh::SetTextureCoordVertices(std::vector<glm::vec2>& texCoords) {
	verticesTexCoord = texCoords;
}


void StaticMesh::SetColorVertices(std::vector<glm::vec3>& colors) {
	verticesColor = colors;
}


void StaticMesh::SetIndices(std::vector<unsigned int>& indices) {
	this->indices = indices;
}


void StaticMesh::Prepare(void) {

	if (!CheckDataConsistency()) {
		return;
	}

	size_t dataSize = verticesPosition.size() * 3 + verticesNormal.size() * 3 + verticesTexCoord.size() * 2;
	
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

		if (!verticesNormal.empty()) {
			data.push_back(verticesNormal[i].x);
			data.push_back(verticesNormal[i].y);
			data.push_back(verticesNormal[i].z);
		}

		if (!verticesTexCoord.empty()) {
			data.push_back(verticesTexCoord[i].x);
			data.push_back(verticesTexCoord[i].y);
		}	

		if (!verticesColor.empty()) {
			data.push_back(verticesColor[i].x);
			data.push_back(verticesColor[i].y);
			data.push_back(verticesColor[i].z);
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

	if (!verticesNormal.empty()) {
		stride += 3 * sizeof(float);
	}
	if (!verticesTexCoord.empty()) {
		stride += 2 * sizeof(float);
	}	
	if (!verticesColor.empty()) {
		stride += 3 * sizeof(float);
	}

	GLsizei offset = 0;	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(0);
	offset += 3 * sizeof(float);

	if (!verticesNormal.empty()) {
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(1);
		offset += 3 * sizeof(float);
	}

	if (!verticesTexCoord.empty()) {
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(2);
		offset += 2 * sizeof(float);
	}

	if (!verticesColor.empty()) {
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(3);
		offset += 3 * sizeof(float);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	verticesPosition.clear();
	verticesNormal.clear();
	verticesTexCoord.clear();	
	verticesColor.clear();
	indices.clear();
}


void StaticMesh::Draw(void) {
	glBindVertexArray(vao);
	if (ebo == 0) {
		glDrawArrays(glMode, 0, nrElements);
	}
	else {
		glDrawElements(glMode, nrElements, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}


bool StaticMesh::CheckDataConsistency(void) const {

	size_t vertexCount = verticesPosition.size();

	if (!indices.empty()) {
		auto it = std::max_element(indices.begin(), indices.end());

		if (*it > vertexCount - 1) {
			//TODO: LOG ERROR!
			std::cout << "ERROR::MESH: DATA INCONSISTENT" << std::endl;
			return false;
		}

		//TODO: Amend this by normals & tex coord checks!
	}

	return true;
}
