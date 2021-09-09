#include "VoxelScene.h"
#include <cmath>


VoxelScene::VoxelScene() { }


VoxelScene::~VoxelScene() { }


char VoxelScene::GetBlock(const glm::ivec3& pos) {
	auto key = CalcSectionPosKey(pos);
	if (sections.find(key) == sections.end()) {
		return 0;
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


SectionsMap& VoxelScene::GetSectionsMap(void) {
	return sections;
}



VoxelGround& VoxelScene::GetGround(void) {
	return ground;
}


void VoxelScene::GenerateMeshes(void) {
	for (auto it = sections.begin(); it != sections.end(); ++it) {
		if (it->second->GetMeshesAreDirty() == true) {
			it->second->GenerateMeshes();
		}
	}

	ground.GenerateMesh();
}




std::array<int, 3> VoxelScene::CalcSectionPosKey(const glm::ivec3& pos) {
	std::array<int, 3> a = { 0 };

	float xf = static_cast<float>(pos.x);
	float xq = xf / static_cast<float>(Section::sectionSize);
	a[0] = static_cast<int>(floor(xq));

	float yf = static_cast<float>(pos.y);
	float yq = yf / static_cast<float>(Section::sectionSize);
	a[1] = static_cast<int>(floor(yq));
	
	float zf = static_cast<float>(pos.z);
	float zq = zf / static_cast<float>(Section::sectionSize);
	a[2] = static_cast<int>(floor(zq));

	return a;
}


glm::ivec3 VoxelScene::ToSectionCoords(const glm::ivec3& pos) {
	glm::ivec3 sp{ 0 };

	if (pos.x >= 0) {
		sp.x = pos.x % static_cast<int>(Section::sectionSize);
	}
	else {
		sp.x = Section::sectionSize - abs(pos.x % static_cast<int>(Section::sectionSize));
		//TODO: This bounds check is Ugly af. Rethink the mathematical way of how to calculate the intervals < 0 !!
		if (sp.x == Section::sectionSize) {
			sp.x = 0;
		}
	}

	if (pos.y >= 0) {
		sp.y = pos.y % static_cast<int>(Section::sectionSize);
	}
	else {
		sp.y = Section::sectionSize - abs(pos.y % static_cast<int>(Section::sectionSize));
		if (sp.y == Section::sectionSize) {
			sp.y = 0;
		}
	}
	
	if (pos.z >= 0) {
		sp.z = pos.z % static_cast<int>(Section::sectionSize);
	}
	else {
		sp.z = Section::sectionSize - abs(pos.z % static_cast<int>(Section::sectionSize));
		if (sp.z == Section::sectionSize) {
			sp.z = 0;
		}
	}
	
	
	return sp;
}