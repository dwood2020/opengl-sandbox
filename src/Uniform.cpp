#include "Uniform.h"


Uniform::Uniform(int value) : value(value) { }


Uniform::Uniform(float value): value(value) { }


Uniform::Uniform(const glm::vec3& value): value(value) { }


Uniform::Uniform(const glm::mat4& value): value(std::make_shared<glm::mat4>(value)) { }


UniformType Uniform::GetType(void) const {
	return (UniformType)value.index();
}

//TODO: Add type checks!
int Uniform::GetInt(void) const {
	return std::get<(size_t)UniformType::Int>(value);
}


float Uniform::GetFloat(void) const {
	return std::get<float>(value);
}


const glm::vec3& Uniform::GetVec3(void) const {
	return std::get<(size_t)UniformType::Vec3>(value);
}


const glm::mat4& Uniform::GetMat4(void) const {
	return *std::get<(size_t)UniformType::Mat4>(value);
}
