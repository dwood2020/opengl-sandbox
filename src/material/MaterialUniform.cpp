#include "MaterialUniform.h"


MaterialUniform::MaterialUniform(): location(-1) { }


MaterialUniform::MaterialUniform(int value) : value(value), location(-1) { }


MaterialUniform::MaterialUniform(float value): value(value), location(-1) { }


MaterialUniform::MaterialUniform(const glm::vec3& value): value(value), location(-1) { }


MaterialUniform::MaterialUniform(const glm::mat4& value): value(std::make_shared<glm::mat4>(value)), location(-1) { }


UniformType MaterialUniform::GetType(void) const {
	return (UniformType)value.index();
}


int MaterialUniform::GetLocation(void) const {
	return location;
}


void MaterialUniform::SetLocation(int location) {
	this->location = location;
}


//TODO: Add type checks!
int MaterialUniform::GetInt(void) const {
	return std::get<(size_t)UniformType::Int>(value);
}


float MaterialUniform::GetFloat(void) const {
	return std::get<float>(value);
}


const glm::vec3& MaterialUniform::GetVec3(void) const {
	return std::get<(size_t)UniformType::Vec3>(value);
}


const glm::mat4& MaterialUniform::GetMat4(void) const {
	return *std::get<(size_t)UniformType::Mat4>(value);
}


void MaterialUniform::UpdateValue(int value) {
	if (((UniformType)this->value.index()) == UniformType::Int) {
		this->value = value;
	}
}


void MaterialUniform::UpdateValue(float value) {
	if (((UniformType)this->value.index()) == UniformType::Float) {
		this->value = value;
	}
}


void MaterialUniform::UpdateValue(const glm::vec3& value) {
	if (((UniformType)this->value.index()) == UniformType::Vec3) {
		this->value = value;
	}
}


void MaterialUniform::UpdateValue(const glm::mat4& value) {
	if (((UniformType)this->value.index()) == UniformType::Mat4) {
		*std::get<(size_t)UniformType::Mat4>(this->value) = value;
	}
}
