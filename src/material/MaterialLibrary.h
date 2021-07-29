#pragma once
#include <map>
#include <string>
#include <memory>
#include "MaterialBase.h"
#include "FlatMaterial.h"
#include "PhongMaterial.h"
#include "../shader/ShaderFactory.h"


//TODO: Refactor this to use unique_ptrs, as library shall be the sole owner of all materials.
using MaterialsMap = std::map<int, MaterialBase*>;

/// <summary>
/// This class holds (and owns) all materials.
/// 
/// NOTE: Map must hold pointers to be able to support polymorphism.
/// </summary>
class MaterialLibrary final {
private:
	ShaderFactory shaderFactory;
	
	MaterialsMap materials;


	/// <summary>
	/// Constructor.
	/// Creates a set of default materials.
	/// </summary>	
	MaterialLibrary();

public:
	/// <summary>
	/// Destructor.
	/// </summary>
	~MaterialLibrary();

	/// <summary>
	/// Gets the singleton instance.
	/// </summary>	
	/// <returns>MaterialLibrary instance</returns>
	static MaterialLibrary& GetInstance(void);
	
	MaterialLibrary(const MaterialLibrary&) = delete;
	void operator=(const MaterialLibrary&) = delete;

	/// <summary>
	/// Makes a new flat material, adds it to the library and returns a pointer to it.
	/// It is tagged with the given name.
	/// NOTE: If the name already exists, the previously saved material is overwritten.
	/// </summary>
	/// <param name="name">Name tag</param>
	/// <returns>Flat material</returns>
	FlatMaterial* MakeFlatMaterial(int id);

	/// <summary>
	/// Makes a new phong material, adds it to the library and returns a pointer to it.
	/// It is tagged with the given id.
	/// NOTE: If the name already exists, the previously saved material is overwritten.
	/// </summary>
	/// <param name="name">Id</param>
	/// <returns>Phong material</returns>
	PhongMaterial* MakePhongMaterial(int id);

	/// <summary>
	/// Gets a material by its defined id.
	/// </summary>
	/// <param name="name">Material id</param>
	/// <returns>Material</returns>
	MaterialBase* GetMaterial(int id);

	/// <summary>
	/// Gets the entire map of materials.
	/// </summary>	
	/// <returns>Materials map</returns>
	MaterialsMap* GetMaterialsMap(void);

};



