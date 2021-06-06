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