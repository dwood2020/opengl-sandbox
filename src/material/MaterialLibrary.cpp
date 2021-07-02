#include "MaterialLibrary.h"


MaterialLibrary::MaterialLibrary(ShaderFactory* shaderFactory): shaderFactory(shaderFactory) { }


MaterialLibrary::~MaterialLibrary() {
    //TODO: refactor this when migrating to unique_ptr
    for (auto it = materials.begin(); it != materials.end(); ++it) {
        delete it->second;
    }
}


FlatMaterial* MaterialLibrary::MakeFlatMaterial(int id) {    
    /*materials[name] = std::make_unique<MaterialBase>(shaderFactory->MakeDefaultFlatShaderProgram());    
    return reinterpret_cast<FlatMaterial*>(materials[name].get());*/
    if (materials.find(id) != materials.end()) {
        delete materials[id];
    }
    materials[id] = new FlatMaterial(shaderFactory->MakeDefaultFlatShaderProgram());
    return dynamic_cast<FlatMaterial*>(materials[id]);

    //TODO: Examine reinterpret_cast vs. static_cast
    //TODO: Move to smart memory management
}


PhongMaterial* MaterialLibrary::MakePhongMaterial(int id) {
    if (materials.find(id) != materials.end()) {
        delete materials[id];
    }
    materials[id] = new PhongMaterial(shaderFactory->MakeDefaultPhongShaderProgram());
    return dynamic_cast<PhongMaterial*>(materials[id]);
}


MaterialBase* MaterialLibrary::GetMaterial(int id) {
    auto it = materials.find(id);
    if (it != materials.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}


MaterialsMap* MaterialLibrary::GetMaterialsMap(void) {
    return &materials;
}
