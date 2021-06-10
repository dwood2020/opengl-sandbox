#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "OctreeNode.h"


class OctreeManager final {
private:
	// IDEA: manager owns all nodes, independently of their actual structure
	std::vector<std::unique_ptr<OctreeNode>> nodeInstances;

public:
	OctreeNode* rootNode;

public:
	OctreeManager();

	~OctreeManager();


	void AddLeaf(const glm::vec3& pos);
};

