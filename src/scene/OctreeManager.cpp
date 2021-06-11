#include "OctreeManager.h"


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

}


OctreeNode* OctreeManager::GetNewNode(void) {
	nodeInstances.push_back(std::make_unique<OctreeNode>());
	return nodeInstances.back().get();
}
