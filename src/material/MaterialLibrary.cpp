#include "MaterialLibrary.h"


MaterialLibrary::MaterialLibrary(ShaderFactory* shaderFactory): shaderFactory(shaderFactory) { }


MaterialLibrary::~MaterialLibrary() {
    //TODO: refactor this when migrating to unique_ptr
    for (auto it = materials.begin(); it != materials.end(); ++it) {
        delete it->second;
    }
}


FlatMaterial* MaterialLibrary::MakeFlatMaterial(const std::string& name) {    
    /*materials[name] = std::make_unique<MaterialBase>(shaderFactory->MakeDefaultFlatShaderProgram());    
    return reinterpret_cast<FlatMaterial*>(materials[name].get());*/
    if (materials.find(name) != materials.end()) {
        delete materials[name];
    }
    materials[name] = new FlatMaterial(shaderFactory->MakeDefaultFlatShaderProgram());
    return dynamic_cast<FlatMaterial*>(materials[name]);

    //TODO: Examine reinterpret_cast vs. static_cast
    //TODO: Move to smart memory management
}


PhongMaterial* MaterialLibrary::MakePhongMaterial(const std::string& name) {
    if (materials.find(name) != materials.end()) {
        delete materials[name];
    }
    materials[name] = new PhongMaterial(shaderFactory->MakeDefaultPhongShaderProgram());
    return dynamic_cast<PhongMaterial*>(materials[name]);
}


const MaterialBase* MaterialLibrary::GetMaterial(const std::string& name) const {
    auto it = materials.find(name);
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
