#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Uniform.h"

// test of new mesh class
std::vector<glm::vec3> vertices = {
	{-0.5f, -0.5f, 0.0f},
	{0.5f, -0.5f, 0.0f},
	{-0.5f, 0.5f, 0.0f},
	{0.5f, 0.5f, 0.0f}
};

std::vector<unsigned int> indices = {
	0, 1, 2,
	2, 3, 1
};

Mesh mesh;
mesh.SetPositionVertices(vertices);
mesh.SetIndices(indices);
mesh.Prepare();
mesh.SetMode(GL_TRIANGLES);


//test: Uniform class
std::vector<Uniform> uniforms;
uniforms.push_back(Uniform(1));
uniforms.push_back(Uniform(glm::vec3(1.0f)));
uniforms.push_back(Uniform(glm::mat4(1.0f)));

glm::mat4 testmatrix = uniforms[2].GetMat4();
glm::vec4 testvec = glm::vec4(1.0f, 2.0f, 3.0f, 1.0f);
glm::vec4 result = testmatrix * testvec;
glm::mat4 refMatrix = glm::mat4(1.0f);
glm::vec4 refResult = refMatrix * testvec;
//Result: Working!!


// test of Uniform UpdateValue member fns
Uniform uniInt(10);
Uniform uniVec3(glm::vec3(10.0f));

std::cout << "uniInt type: " << (int)uniInt.GetType() << "  value: " << uniInt.GetInt() << std::endl;

uniInt.UpdateValue(20);
std::cout << "uniInt type: " << (int)uniInt.GetType() << "  value: " << uniInt.GetInt() << std::endl;

std::cout << "uniVec3 type: " << (int)uniVec3.GetType() << "  value: " << uniVec3.GetVec3().x << " " << uniVec3.GetVec3().y << " " << uniVec3.GetVec3().z << std::endl;
uniVec3.UpdateValue(glm::vec3(100.0f, 200.0f, 300.0f));
std::cout << "uniVec3 type: " << (int)uniVec3.GetType() << "  value: " << uniVec3.GetVec3().x << " " << uniVec3.GetVec3().y << " " << uniVec3.GetVec3().z << std::endl;

Uniform uniMat4(glm::mat4(1.0f));
std::cout << "uniMat4 type: " << (int)uniMat4.GetType() << "  value 0,0: " << uniMat4.GetMat4()[0][0] << std::endl;
uniMat4.UpdateValue(glm::mat4(25.0f));
std::cout << "uniMat4 type: " << (int)uniMat4.GetType() << "  value 0,0: " << uniMat4.GetMat4()[0][0] << std::endl;
// Result: Working



// Test: Dynamic mesh class
DynamicMesh dynamicMesh;
std::vector<VertexPosNorm>* vertexRef = &dynamicMesh.GetVerticesPosNorm();

// plane vertices:
glm::vec3 lb = glm::vec3(0.0f);
glm::vec3 rb = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 rt = glm::vec3(1.0f, 1.0f, 0.0f);
glm::vec3 lt = glm::vec3(0.0f, 1.0f, 0.0f);

// plane normals:
glm::vec3 n = glm::vec3(0.0f, 0.0f, 1.0f);

VertexPosNorm vLb;
vLb = { lb, n };

VertexPosNorm vRb;
vRb.pos = rb;
vRb.norm = n;
VertexPosNorm vRt;
vRt.pos = rt;
vRt.norm = n;
VertexPosNorm vLt;
vLt.pos = lt;
vLt.norm = n;

vertexRef->push_back(vLb);
vertexRef->push_back(vRb);
vertexRef->push_back(vRt);

vertexRef->push_back(vLb);
vertexRef->push_back(vRt);
vertexRef->push_back(vLt);

glm::vec3 move = glm::vec3(1.0f, 0.0f, -8.0f);
for (VertexPosNorm& v : *vertexRef) {
	v.pos += move;
}

dynamicMesh.SetGlMode(GL_TRIANGLES);
dynamicMesh.Prepare();

// + add rendercommand



// Test: block template faces in Section class
glm::mat4 MfaceTemplate = glm::mat4(1.0f);
MfaceTemplate = glm::translate(MfaceTemplate, glm::vec3(3.0f, 0.0f, -6.0f));

DynamicMesh templateTestMesh;
templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), Section::frontFaceTemplate.begin(), Section::frontFaceTemplate.end());
templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), Section::rightFaceTemplate.begin(), Section::rightFaceTemplate.end());
templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), Section::rearFaceTemplate.begin(), Section::rearFaceTemplate.end());
templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), Section::leftFaceTemplate.begin(), Section::leftFaceTemplate.end());
templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), Section::topFaceTemplate.begin(), Section::topFaceTemplate.end());
templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), Section::bottomFaceTemplate.begin(), Section::bottomFaceTemplate.end());
templateTestMesh.SetGlMode(GL_TRIANGLES);
templateTestMesh.Prepare();



// test mesh generation
Section section000(glm::ivec3(0));
section000.SetBlock(glm::ivec3(1, 1, 1), 2);
section000.SetBlock(glm::ivec3(2, 1, 1), 2);
section000.SetBlock(glm::ivec3(2, 1, 2), 2);
section000.SetBlock(glm::ivec3(4, 1, 5), 3);
section000.SetBlock(glm::ivec3(4, 0, 5), 3);
section000.SetBlock(glm::ivec3(2, 2, 2), 1);
section000.SetBlock(glm::ivec3(0), 1);
section000.SetBlock(glm::ivec3(0, 0, 1), 1);
section000.SetBlock(glm::ivec3(0, 1, 1), 1);

section000.SetBlock(glm::ivec3(7, 7, 7), 3);
for (int i = 0; i < 8; i++) {
	section000.SetBlock(glm::ivec3(7, 0, i), 1);
}

for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
		for (int k = 5; k < 8; k++) {
			section000.SetBlock(glm::ivec3(i, j, k), 1);
		}
	}
}

section000.SetBlock(glm::ivec3(2, 2, 7), 2);

section000.GenerateMeshes();



// test voxelscene

auto k1 = voxelScene.CalcSectionPosKey({ 1,2,3 });	// should be 0,0,0
auto k2 = voxelScene.CalcSectionPosKey({ 1,0,-5 });	// should be 0,0,-1
auto k3 = voxelScene.CalcSectionPosKey({ 1,0,-12 });// should be 0,0,-2
auto k4 = voxelScene.CalcSectionPosKey({ 1,0,12 });	// should be 0,0,1