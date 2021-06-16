#pragma once
#include <array>
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include "Section.h"


class BlockManager final {
private:
	/*std::map<glm::ivec3, std::unique_ptr<Section>> sections;*/
	std::map<std::array<int, 3>, std::unique_ptr<Section>> sections;

public:
	BlockManager();

	~BlockManager();


	char GetBlock(const glm::ivec3& pos);	


	void SetBlock(const glm::ivec3& pos, char block);


private:
	/*glm::ivec3 CalcSectionPos(const glm::ivec3& pos);*/

	std::array<int, 3> CalcSectionPosKey(const glm::ivec3& pos);

	glm::ivec3 ToSectionCoords(const glm::ivec3& pos);
};



