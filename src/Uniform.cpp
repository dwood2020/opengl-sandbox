#include "Uniform.h"


Uniform::Uniform(): location(-1) { }


Uniform::Uniform(int value) : value(value), location(-1) { }


Uniform::Uniform(float value): value(value), location(-1) { }


Uniform::Uniform(const glm::vec3& value): value(value), location(-1) { }


Uniform::Uniform(const glm::mat4& value): value(std::make_shared<glm::mat4>(value)), location(-1) { }


UniformType Uniform::GetType(void) const {
	return (UniformType)value.index();
}


int Uniform::GetLocation(void) const {
	return location;
}


void Uniform::SetLocation(int location) {
	this->location = location;
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


void Uniform::UpdateValue(int value) {
	if (((UniformType)this->value.index()) == UniformType::Int) {
		this->value = value;
	}
}


void Uniform::UpdateValue(float value) {
	if (((UniformType)this->value.index()) == UniformType::Float) {
		this->value = value;
	}
}


void Uniform::UpdateValue(const glm::vec3& value) {
	if (((UniformType)this->value.index()) == UniformType::Vec3) {
		this->value = value;
	}
}


void Uniform::UpdateValue(const glm::mat4& value) {

}
