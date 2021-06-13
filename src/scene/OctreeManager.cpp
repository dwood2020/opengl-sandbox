#include "OctreeManager.h"
#include <cmath>
#include <string>


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
	bool insideRootBounds = IsInsideBounds(newNode, rootNode);

	
	if (insideRootBounds) {
		// iterate to the new leaf's direct parent node
		OctreeNode* directParent = rootNode;
		int directParentOctet = GetOctet(newNode->position, directParent->position);
		while (directParent->level > newNode->level + 1) {
			OctreeNode* newParent = GetNewNode();
			newParent->level = directParent->level - 1;
			directParent->AddChild(newParent, directParentOctet);
			
			directParent = newParent;
			directParentOctet = GetOctet(newNode->position, directParent->position);
		}

		directParent->AddChild(newNode, directParentOctet);

	}
	else {

	}


}


bool OctreeManager::IsInsideBounds(OctreeNode* node, OctreeNode* root) const {
	bool insideRootBounds = true;

	for (unsigned int i = 0; i < 3; i++) {
		if (abs(node->position[i] - root->position[i]) > root->level) {
			insideRootBounds = false;
			break;
		}
	}

	return insideRootBounds;
}


int OctreeManager::GetOctet(const glm::vec3& pos, const glm::vec3& rootCenter) {
	
	std::string octet = "xxx";
	octet[0] = ((pos.x > rootCenter.x) ? '+' : '-');
	octet[1] = ((pos.y > rootCenter.y) ? '+' : '-');
	octet[2] = ((pos.z > rootCenter.z) ? '+' : '-');
	
	if (octet == "+++") return 0;
	if (octet == "-++") return 1;
	if (octet == "--+") return 2;
	if (octet == "+-+") return 3;
	if (octet == "++-") return 4;
	if (octet == "-+-") return 5;
	if (octet == "---") return 6;
	if (octet == "+--") return 7;

	return -1;
}


OctreeNode* OctreeManager::GetNewNode(void) {
	nodeInstances.push_back(std::make_unique<OctreeNode>());
	return nodeInstances.back().get();
}
