#include "VoxelScene.h"


VoxelScene::VoxelScene() { }


VoxelScene::~VoxelScene() { }


char VoxelScene::GetBlock(const glm::ivec3& pos) {
	auto key = CalcSectionPosKey(pos);
	if (sections.find(key) == sections.end()) {
		return -1;
	}
	return sections[key]->GetBlock(ToSectionCoords(pos));
}


void VoxelScene::SetBlock(const glm::ivec3& pos, char block) {

	auto key = CalcSectionPosKey(pos);
	if (sections.find(key) == sections.end()) {
		sections[key] = std::make_unique<Section>(glm::ivec3(key[0], key[1], key[2]));
	}

	sections[key]->SetBlock(ToSectionCoords(pos), block);
}


SectionsMap& VoxelScene::GetSections(void) {
	return sections;
}


void VoxelScene::GenerateMeshes(void) {
	for (auto it = sections.begin(); it != sections.end(); ++it) {
		if (it->second->GetMeshesAreDirty() == true) {
			it->second->GenerateMesh();
		}
	}
}




std::array<int, 3> VoxelScene::CalcSectionPosKey(const glm::ivec3& pos) {
	std::array<int, 3> a = { 0 };
	a[0] = pos.x / Section::sectionSize;
	a[1] = pos.y / Section::sectionSize;
	a[2] = pos.z / Section::sectionSize;
	return a;
}


glm::ivec3 VoxelScene::ToSectionCoords(const glm::ivec3& pos) {
	glm::ivec3 sp{ 0 };
	sp.x = pos.x % Section::sectionSize;
	sp.y = pos.y % Section::sectionSize;
	sp.z = pos.z % Section::sectionSize;
	return sp;
}