#include "Section.h"
#include <cmath>


// initialize static template faces
std::vector<VertexPosNorm> Section::frontFaceTemplate = {
	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)}
};

std::vector<VertexPosNorm> Section::rightFaceTemplate = {
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}
};

std::vector<VertexPosNorm> Section::rearFaceTemplate = {
	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},

	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}
};

std::vector<VertexPosNorm> Section::leftFaceTemplate = {
	{glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},

	{glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}
};

std::vector<VertexPosNorm> Section::topFaceTemplate = {
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}
};

std::vector<VertexPosNorm> Section::bottomFaceTemplate = {
	{glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},

	{glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)}
};


Section::Section(const glm::ivec3& basePos) : blocks{0}, basePos(basePos) { }


Section::~Section() { }


char Section::GetBlock(const glm::ivec3& pos) {	
	if (!IsWithinBounds(pos)) {
		return -1;
	}
	else {
		return blocks[pos.x][pos.y][pos.z];
	}	
}


char Section::GetBlock(const glm::vec3& pos) {	
	return GetBlock(FloatToInt(pos));
}


void Section::SetBlock(const glm::ivec3& pos, char block) {
	if (!IsWithinBounds(pos)) {
		return;
	}

	blocks[pos.x][pos.y][pos.z] = block;
}


void Section::SetBlock(const glm::vec3& pos, char block) {
	SetBlock(FloatToInt(pos), block);
}


Section::ArrayPtr Section::GetArray(void) {
	return &blocks;
}


void Section::GenerateMesh(void) {

}


// private helper methods ----------------------------------------------

bool Section::IsWithinBounds(const glm::ivec3& pos) const {
	if (pos.x >= sectionSize || pos.y >= sectionSize || pos.z >= sectionSize) {
		return false;
	}
	else {
		return true;
	}
}


glm::ivec3 Section::FloatToInt(const glm::vec3& fv) const {
	glm::ivec3 iv{ 0 };
	iv.x = static_cast<int>(floor(fv.x));
	iv.y = static_cast<int>(floor(fv.y));
	iv.z = static_cast<int>(floor(fv.z));
	return iv;
}