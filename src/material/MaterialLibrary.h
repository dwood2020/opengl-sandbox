#pragma once
#include <map>
#include <string>
#include <memory>
#include "MaterialBase.h"
#include "FlatMaterial.h"
#include "PhongMaterial.h"
#include "../shader/ShaderFactory.h"


/// <summary>
/// This class holds (and owns) all materials.
/// 
/// NOTE: Map must hold pointers to be able to support polymorphism.
/// </summary>
class MaterialLibrary final {
private:
	ShaderFactory* shaderFactory;

	//TODO: Refactor this to use unique_ptrs, as library shall be the sole owner of all materials.
	std::map<std::string, MaterialBase*> materials;


	MaterialLibrary() = default;

public:
	/// <summary>
	/// Constructor. Shader factory reference is mandatory.
	/// Creates a set of default materials.
	/// </summary>
	/// <param name="shaderFactory">Shader factory</param>
	MaterialLibrary(ShaderFactory* shaderFactory);

	
	~MaterialLibrary();


	FlatMaterial* MakeFlatMaterial(const std::string& name);


	PhongMaterial* MakePhongMaterial(const std::string& name);


	const MaterialBase* GetMaterial(const std::string& name) const;
};



