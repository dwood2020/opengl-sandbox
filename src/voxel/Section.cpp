#include "Section.h"
#include <cmath>


Section::Section() : blocks{0} { }


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