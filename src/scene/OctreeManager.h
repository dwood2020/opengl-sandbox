#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "OctreeNode.h"


class OctreeManager final {
private:
	// IDEA: manager owns all nodes, independently of their actual structure
	std::vector<std::unique_ptr<OctreeNode>> nodeInstances;

	//IDEA: "pos" ist northwest bottom corner, "center" is actual center position of node
	const glm::vec3 posCenterOffset = glm::vec3(0.5f, 0.5f, 0.5f);

public:
	OctreeNode* rootNode;

public:
	OctreeManager();

	~OctreeManager();


	void AddLeaf(const glm::vec3& pos);

private:
	bool IsInsideBounds(OctreeNode* node, OctreeNode* root) const;

	int GetOctet(const glm::vec3& pos, const glm::vec3& rootCenter);

	OctreeNode* GetNewNode(void);
};

