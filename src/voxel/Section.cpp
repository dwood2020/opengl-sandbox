#include "Section.h"
#include <cmath>


Section::Section(): blocks{ 0 } { }


Section::~Section() { }


char Section::GetBlock(int x, int y, int z) {	
	if (x >= sectionSize || y >= sectionSize || z >= sectionSize) {
		return -1;
	}
	else {
		return blocks[x][y][z];
	}

	
}


char Section::GetBlock(const glm::vec3& pos) {
	int x = static_cast<int>(floor(pos.x));
	int y = static_cast<int>(floor(pos.y));
	int z = static_cast<int>(floor(pos.z));

	return GetBlock(x, y, z);
}
