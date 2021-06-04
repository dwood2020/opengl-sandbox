#pragma once
#include <map>
#include <string>
#include <memory>
#include "MaterialBase.h"


/// <summary>
/// This class holds (and owns) all materials.
/// 
/// NOTE: Map must hold pointers to be able to support polymorphism.
/// They are realized as unique_ptrs as a material shall have the library as it's sole owner.
/// </summary>
class MaterialLibrary final {
private:
	std::map<std::string, std::unique_ptr<MaterialBase>> materials;

public:
	/// <summary>
	/// Constructor.
	/// Creates a set of default materials.
	/// </summary>
	MaterialLibrary();

	~MaterialLibrary();
};



