#pragma once
#include <map>
#include <string>
#include <memory>
#include "MaterialBase.h"
#include "FlatMaterial.h"
#include "PhongMaterial.h"
#include "../shader/ShaderFactory.h"


//TODO: Refactor this to use unique_ptrs, as library shall be the sole owner of all materials.
using MaterialsMap = std::map<std::string, MaterialBase*>;

/// <summary>
/// This class holds (and owns) all materials.
/// 
/// NOTE: Map must hold pointers to be able to support polymorphism.
/// </summary>
class MaterialLibrary final {
private:
	ShaderFactory* shaderFactory;

	
	MaterialsMap materials;


	MaterialLibrary() = default;

public:
	/// <summary>
	/// Constructor. Shader factory reference is mandatory.
	/// Creates a set of default materials.
	/// </summary>
	/// <param name="shaderFactory">Shader factory</param>
	MaterialLibrary(ShaderFactory* shaderFactory);

	/// <summary>
	/// Destructor.
	/// </summary>
	~MaterialLibrary();

	/// <summary>
	/// Makes a new flat material, adds it to the library and returns a pointer to it.
	/// It is tagged with the given name.
	/// NOTE: If the name already exists, the previously saved material is overwritten.
	/// </summary>
	/// <param name="name">Name tag</param>
	/// <returns>Flat material</returns>
	FlatMaterial* MakeFlatMaterial(const std::string& name);

	/// <summary>
	/// Makes a new phong material, adds it to the library and returns a pointer to it.
	/// It is tagged with the given name.
	/// NOTE: If the name already exists, the previously saved material is overwritten.
	/// </summary>
	/// <param name="name">Name tag</param>
	/// <returns>Phong material</returns>
	PhongMaterial* MakePhongMaterial(const std::string& name);


	MaterialBase* GetMaterial(const std::string& name);


	MaterialsMap* GetMaterialsMap(void);

};



