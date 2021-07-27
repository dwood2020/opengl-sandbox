#include "Renderer.h"
#include "../glad/glad.h"
#include "../material/MaterialBase.h"
#include <algorithm>

#include <iostream>


bool Renderer::LoadGL(void) {
	if (!gladLoadGL()) {
		std::cout << "Renderer::LoadGL: gladLoadGL failed" << std::endl;
		return false;
	}
	return true;
}


Renderer::Renderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, MaterialLibrary& materialLibrary): 
	lighting(&lighting), camera(&camera), materialLibrary(&materialLibrary), voxelScene(nullptr), defaultBlockMaterial(nullptr) {
	
	// register for events
	eventBus.AddListener(EventType::WindowResize, this);
}


Renderer::~Renderer() { }


void Renderer::OnEvent(Event& e) {
	if (e.GetType() == EventType::WindowResize) {
		auto& eResize = (WindowResizeEvent&)e;
		glm::vec2 rect = glm::vec2(eResize.GetScreenWidth(), eResize.GetScreenHeight());
		CalculateViewport(rect);

		std::cout << "Window resize event handled in Renderer" << std::endl;
	}
}


void Renderer::Init(const glm::vec2& windowRect) {
	CalculateViewport(windowRect);
	
	glEnable(GL_DEPTH_TEST);
	
	stateHandler.SetBlending(true);
	stateHandler.SetFaceCulling(true);
}


void Renderer::SetClearColor(const glm::vec3& clearColor) {
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
}


void Renderer::SetGlPolygonMode(GLenum mode) {
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}


SimpleRenderCommand* Renderer::AddSimpleCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return nullptr;
	}

	//SimpleRenderCommand command(modelMatrix, mesh, material);
	simpleRenderCommands.push_back(std::make_unique<SimpleRenderCommand>(modelMatrix, mesh, material));

	return simpleRenderCommands.back().get();
}


void Renderer::AddVoxelScene(VoxelScene& voxelScene, MaterialBase* defaultBlockMaterial) {
	this->voxelScene = &voxelScene;	
	this->defaultBlockMaterial = defaultBlockMaterial;
}


//void Renderer::AddBlockMaterialMapping(char blockTypeId, MaterialBase* material) {
//	blockMaterialMap.insert(std::pair<char, MaterialBase*>(blockTypeId, material));
//}


void Renderer::Prepare(void) {

	MaterialsMap* mats = materialLibrary->GetMaterialsMap();
	
	for (auto it = mats->begin(); it != mats->end(); ++it) {
		MaterialBase* material = it->second;

		// prepare the material
		material->Prepare();

		// do initial set
		material->SetViewProjectionMatrixUniform(camera->GetViewProjectionMatrix());
		if (material->GetAffectedByLight()) {
			material->SetViewPosUniform(camera->GetPosition());
			lighting->SetUniforms(material->GetShaderProgram());
		}
	}

	SortSimpleCommands();
}


void Renderer::DoFrame(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// voxelscene render commands first:
	if (voxelScene != nullptr) {
		DoVoxelScene();
	}
	
	// simple render commands last, because they can contain transparent materials
	DoSimpleCommands();


	if (camera->GetViewProjectionMatrixIsDirty() == true) {
		camera->ResetDirtyState();		
	}

}

//TODO: Make Sorting a separate public method!
void Renderer::SortSimpleCommands(void) {
	
	std::sort(simpleRenderCommands.begin(), simpleRenderCommands.end(),
		[](const std::unique_ptr<SimpleRenderCommand>& a, const std::unique_ptr<SimpleRenderCommand>& b) -> bool {
			
			//super simple sorting which puts transparent materials at the end
			return a->GetMaterial()->GetTransparent() < b->GetMaterial()->GetTransparent();
		});

}


void Renderer::DoSimpleCommands(void) {
	
	for (unsigned int i = 0; i < simpleRenderCommands.size(); ++i) {
		SimpleRenderCommand* command = simpleRenderCommands[i].get();		

		command->material->Bind();

		if (camera->GetViewProjectionMatrixIsDirty() == true) {
			command->material->SetViewProjectionMatrixUniform(camera->GetViewProjectionMatrix());

			if (command->material->GetAffectedByLight() == true) {
				command->material->SetViewPosUniform(camera->GetPosition());
			}
		}

		//NOTE: PV uniform must be set also for inactive commands, so that it is correct once it is activated
		if (!command->isActive) {
			command->material->Unbind();
			continue;
		}

		command->material->SetModelMatrixUniform(command->M);
		command->mesh->Draw();
		command->material->Unbind();
	}
}


// assuming that voxelscene is no nullptr here
void Renderer::DoVoxelScene(void) {

	// iterate over all sections
	for (auto itSection = voxelScene->GetSectionsMap().begin(); itSection != voxelScene->GetSectionsMap().end(); ++itSection) {

		// iterate over each mesh per section
		for (auto itMesh = itSection->second->GetMeshes().begin(); itMesh != itSection->second->GetMeshes().end(); ++itMesh) {
						
			int materialId = static_cast<int>(itMesh->first);
			MaterialBase* material = materialLibrary->GetMaterial(materialId);
			
			if (material == nullptr) {
				material = defaultBlockMaterial;
			}			

			material->Bind();	// This is IMPORTANT 

			//TEMP
			material->SetModelMatrixUniform(glm::mat4(1.0f));

			//TODO: This is redundant! Think about different solution
			if (camera->GetViewProjectionMatrixIsDirty()) {
				material->SetViewProjectionMatrixUniform(camera->GetViewProjectionMatrix());
				if (material->GetAffectedByLight()) {
					material->SetViewPosUniform(camera->GetPosition());
				}
			}

			
			itMesh->second.Draw();
			material->Unbind();
		}

	}

}


void Renderer::CalculateViewport(const glm::vec2& rect) {
	glViewport(0, 0, static_cast<GLsizei>(rect.x), static_cast<GLsizei>(rect.y));
}


