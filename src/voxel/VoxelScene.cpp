#include "VoxelScene.h"


VoxelScene::VoxelScene() {
	
	// initialize block face templates
	frontFaceTemplate.reserve(6);
	rightFaceTemplate.reserve(6);
	rearFaceTemplate.reserve(6);
	leftFaceTemplate.reserve(6);
	topFaceTemplate.reserve(6);
	bottomFaceTemplate.reserve(6);

	frontFaceTemplate = {
		{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

		{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)}
	};

	rightFaceTemplate = {
		{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

		{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}
	};

	rearFaceTemplate = {
		{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},

		{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}
	};

	leftFaceTemplate = {
		{glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},

		{glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}
	};

	topFaceTemplate = {
		{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

		{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}
	};

	bottomFaceTemplate = {
		{glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},

		{glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)}
	};

}


VoxelScene::~VoxelScene() {

	for (unsigned int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
	}
}


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
		sections[key] = std::make_unique<Section>();
	}

	sections[key]->SetBlock(ToSectionCoords(pos), block);
}


SectionsMap& VoxelScene::GetSections(void) {
	return sections;
}


void VoxelScene::GenerateMeshes(void) {

	glm::vec3 blockPos = glm::vec3(0.0f);

	for (auto it = sections.begin(); it != sections.end(); ++it) {
		blockPos = { static_cast<float>(it->first[0]), static_cast<float>(it->first[1]), static_cast<float>(it->first[2]) };


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