#include "BlockManager.h"


BlockManager::BlockManager() { }


BlockManager::~BlockManager() { }


char BlockManager::GetBlock(const glm::ivec3& pos) {
	auto key = CalcSectionPosKey(pos);
	if (sections.find(key) == sections.end()) {
		return -1;
	}	
	return sections[key]->GetBlock(ToSectionCoords(pos));
}


void BlockManager::SetBlock(const glm::ivec3& pos, char block) {
	/*sections[{pos.x / 16, pos.y / 16, pos.z / 16}]->SetBlock({ pos.x % 16, pos.y % 16, pos.z % 16 }, block);*/
	//sections[CalcSectionPos(pos)];

	auto key = CalcSectionPosKey(pos);
	if (sections.find(key) == sections.end()) {
		sections[key] = std::make_unique<Section>();
	}

	sections[CalcSectionPosKey(pos)]->SetBlock(ToSectionCoords(pos), block);
}


//glm::ivec3 BlockManager::CalcSectionPos(const glm::ivec3& pos) {
//	glm::ivec3 p{0};
//	p.x = pos.x / Section::sectionSize;
//	p.y = pos.y / Section::sectionSize;
//	p.z = pos.z / Section::sectionSize;
//	return p;
//}


std::array<int, 3> BlockManager::CalcSectionPosKey(const glm::ivec3& pos) {
	std::array<int, 3> a = { 0 };
	a[0] = pos.x / Section::sectionSize;
	a[1] = pos.y / Section::sectionSize;
	a[2] = pos.z / Section::sectionSize;
	return a;
}


glm::ivec3 BlockManager::ToSectionCoords(const glm::ivec3& pos) {
	glm::ivec3 sp{0};
	sp.x = pos.x % Section::sectionSize;
	sp.y = pos.y % Section::sectionSize;
	sp.z = pos.z % Section::sectionSize;
	return sp;
}

