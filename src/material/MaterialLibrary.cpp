#include "MaterialLibrary.h"


MaterialLibrary::MaterialLibrary() { }


MaterialLibrary::~MaterialLibrary() {
    //TODO: refactor this when migrating to unique_ptr
    for (auto it = materials.begin(); it != materials.end(); ++it) {
        delete it->second;
    }
}


MaterialLibrary& MaterialLibrary::GetInstance(void) {
    static MaterialLibrary instance;    // guaranteed to be destroyed. Inst'd on 1st use.
    return instance;
}


//TODO: Move id generation into library, add id field to MaterialBase, to take id definition away from the user
FlatMaterial* MaterialLibrary::MakeFlatMaterial(int id) {    
    /*materials[name] = std::make_unique<MaterialBase>(shaderFactory->MakeDefaultFlatShaderProgram());    
    return reinterpret_cast<FlatMaterial*>(materials[name].get());*/
    if (materials.find(id) != materials.end()) {
        delete materials[id];
    }
    materials[id] = new FlatMaterial(shaderFactory.MakeDefaultFlatShaderProgram());
    return dynamic_cast<FlatMaterial*>(materials[id]);
    
    //TODO: Move to smart memory management
}


PhongMaterial* MaterialLibrary::MakePhongMaterial(int id) {
    if (materials.find(id) != materials.end()) {
        delete materials[id];
    }
    materials[id] = new PhongMaterial(shaderFactory.MakeDefaultPhongShaderProgram());
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
