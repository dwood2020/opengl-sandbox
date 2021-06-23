#include "Section.h"
#include <cmath>

#include <iostream>


// initialize static template faces
std::vector<VertexPosNorm> Section::frontFaceTemplate = {
	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)}
};

std::vector<VertexPosNorm> Section::rightFaceTemplate = {
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	{glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}
};

std::vector<VertexPosNorm> Section::rearFaceTemplate = {
	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},

	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}
};

std::vector<VertexPosNorm> Section::leftFaceTemplate = {
	{glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},

	{glm::vec3(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}
};

std::vector<VertexPosNorm> Section::topFaceTemplate = {
	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

	{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}
};

std::vector<VertexPosNorm> Section::bottomFaceTemplate = {
	{glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},

	{glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)}
};


Section::Section(const glm::ivec3& basePos) : blocks{0}, basePos(basePos), meshIsDirty(false) { }


Section::~Section() { }


char Section::GetBlock(const glm::ivec3& pos) {	
	if (!IsWithinBounds(pos)) {
		return -1;
	}
	else {
		return blocks[pos.x][pos.y][pos.z];
	}	
}


char Section::GetBlock(const glm::vec3& pos) {	
	return GetBlock(FloatToInt(pos));
}


void Section::SetBlock(const glm::ivec3& pos, char block) {
	if (!IsWithinBounds(pos)) {
		return;
	}

	blocks[pos.x][pos.y][pos.z] = block;
}


void Section::SetBlock(const glm::vec3& pos, char block) {
	SetBlock(FloatToInt(pos), block);
}


Section::ArrayPtr Section::GetArray(void) {
	return &blocks;
}


void Section::GenerateMesh(void) {
	

	mesh.GetVerticesPosNorm().clear();



	//// first approach:
	//// "sweep through each row in each direction and react to rising and falling edges"
	//char last = 0;

	//// y direction	
	//for (unsigned int i = 0; i < sectionSize; ++i) {
	//	
	//	// z direction
	//	for (unsigned int j = 0; j < sectionSize; ++j) {
	//		
	//		// x direction
	//		for (unsigned int k = 0; k < sectionSize; ++k) {

	//			//rising edge
	//			if (blocks[k][i][j] > last) {
	//				mesh.GetVerticesPosNorm().insert(mesh.GetVerticesPosNorm().end(), leftFaceTemplate.begin(), leftFaceTemplate.end());
	//				last = 1;					
	//			}
	//			//falling edge
	//			else if (blocks[k][i][j] < last) {
	//				mesh.GetVerticesPosNorm().insert(mesh.GetVerticesPosNorm().end(), rightFaceTemplate.begin(), rightFaceTemplate.end());
	//				last = 0;
	//			}
	//			else {
	//				// same, do not add a face
	//			}

	//		}
	//	}
	//}


	// simple, forward approach: iterate over each cell + check all 6 neighbours
	glm::vec3 blockPos = basePos;
	auto& meshVector = mesh.GetVerticesPosNorm();

	for (unsigned int i = 1; i < sectionSize-1; i++) {
		blockPos.x += 1;

		for (unsigned int j = 1; j < sectionSize-1; j++) {
			blockPos.y += 1;

			for (unsigned int k = 1; k < sectionSize-1; k++) {
				/*std::cout << "blocks[" << i << "][" << j << "][" << k << "]: " << (int)blocks[i][j][k] << std::endl;*/
				
				blockPos.x = basePos.x + i;
				blockPos.y = basePos.y + j;
				blockPos.z = basePos.z + k;				

				/*std::cout << "blocks[" << i << "][" << j << "][" << k << "]: pos: " << blockPos.x << " " << blockPos.y << " " << blockPos.z << std::endl;*/

				if (blocks[i][j][k] == 0) {
					continue;
				}

				/*std::cout << "blocks[" << i << "][" << j << "][" << k << "]: " << (int)blocks[i][j][k] << std::endl;*/
				/*std::cout << "blocks[" << i << "][" << j << "][" << k << "]: pos: " << blockPos.x << " " << blockPos.y << " " << blockPos.z << std::endl;*/

				// left face
				if (blocks[i - 1][j][k] == 0) {
					auto leftFace = leftFaceTemplate;
					for (VertexPosNorm& v : leftFace) {
						v.pos += blockPos;
					}
					meshVector.insert(meshVector.end(), leftFace.begin(), leftFace.end());
					std::cout << "inserted left face" << std::endl;
				}

				// right face
				if (blocks[i + 1][j][k] == 0) {
					auto rightFace = rightFaceTemplate;
					for (VertexPosNorm& v : rightFace) {
						v.pos += blockPos;
					}
					meshVector.insert(meshVector.end(), rightFace.begin(), rightFace.end());
					std::cout << "inserted right face" << std::endl;
				}

				// rear face
				if (blocks[i][j][k - 1] == 0) {
					auto rearFace = rearFaceTemplate;
					for (VertexPosNorm& v : rearFace) {
						v.pos += blockPos;
					}
					meshVector.insert(meshVector.end(), rearFace.begin(), rearFace.end());
					std::cout << "inserted rear face" << std::endl;
				}

				// front face
				if (blocks[i][j][k + 1] == 0) {
					auto frontFace = frontFaceTemplate;
					for (VertexPosNorm& v : frontFace) {
						v.pos += blockPos;
					}
					meshVector.insert(meshVector.end(), frontFace.begin(), frontFace.end());
				}

				// bottom face
				if (blocks[i][j - 1][k] == 0) {
					auto face = bottomFaceTemplate;
					for (VertexPosNorm& v : face) {
						v.pos += blockPos;
					}
					meshVector.insert(meshVector.end(), face.begin(), face.end());
				}

				// top face
				if (blocks[i][j + 1][k] == 0) {
					auto face = topFaceTemplate;
					for (VertexPosNorm& v : face) {
						v.pos += blockPos;
					}
					meshVector.insert(meshVector.end(), face.begin(), face.end());
				}

			}
		}
	}

	if (!meshVector.empty()) {
		mesh.SetGlMode(GL_TRIANGLES);
		mesh.Prepare();
		std::cout << "prepared mesh!" << std::endl;
	}	
}


DynamicMesh& Section::GetMesh(void) {
	return mesh;
}


bool Section::GetMeshIsDirty(void) const {
	return meshIsDirty;
}



// private helper methods ----------------------------------------------

bool Section::IsWithinBounds(const glm::ivec3& pos) const {
	if (pos.x >= sectionSize || pos.y >= sectionSize || pos.z >= sectionSize) {
		return false;
	}
	else {
		return true;
	}
}


glm::ivec3 Section::FloatToInt(const glm::vec3& fv) const {
	glm::ivec3 iv{ 0 };
	iv.x = static_cast<int>(floor(fv.x));
	iv.y = static_cast<int>(floor(fv.y));
	iv.z = static_cast<int>(floor(fv.z));
	return iv;
}