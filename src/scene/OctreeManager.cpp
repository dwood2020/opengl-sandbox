#include "OctreeManager.h"
#include <cmath>


OctreeManager::OctreeManager(): rootNode(nullptr) { }


OctreeManager::~OctreeManager() { }


void OctreeManager::AddLeaf(const glm::vec3& pos) {
	if (rootNode == nullptr) {
		// add first node
		OctreeNode* node = GetNewNode();
		node->level = 0;
		node->position = pos + posCenterOffset;
		rootNode = node;
		return;
	}
	
	// added leaf node is not the first node
	OctreeNode* newNode = GetNewNode();
	newNode->position = pos + posCenterOffset;
	newNode->level = 0;

	// check if inside bounds of current root
	bool outOfBounds = false;
	for (unsigned int i = 0; i < 3; i++) {
		if (abs(newNode->position[i] - rootNode->position[i]) < rootNode->level) {
			// within root 
		}
		else {

		}
	}

}


OctreeNode* OctreeManager::GetNewNode(void) {
	nodeInstances.push_back(std::make_unique<OctreeNode>());
	return nodeInstances.back().get();
}
