#include <glm/glm.hpp>
#include "Uniform.h"


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