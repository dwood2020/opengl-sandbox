#include "Renderer.h"
#include "../glad/glad.h"
#include "../material/MaterialLibrary.h"
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


Renderer::Renderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera): 
	lighting(&lighting), camera(&camera), voxelScene(nullptr), defaultBlockMaterial(nullptr),
	groundGridMaterial(nullptr), groundSurfaceMaterial(nullptr) {
	
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
		
	stateHandler.SetDepthTesting(true);
	stateHandler.SetBlending(true);
	stateHandler.SetFaceCulling(true);
}


void Renderer::SetClearColor(const glm::vec3& clearColor) {
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
}


void Renderer::SetGlPolygonMode(GLenum mode) {
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}


RenderCommand* Renderer::AddSimpleCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return nullptr;
	}
	
	renderCommands.push_back(std::make_unique<RenderCommand>(modelMatrix, mesh, material));

	return renderCommands.back().get();
}


void Renderer::AddVoxelScene(VoxelScene& voxelScene, MaterialBase* defaultBlockMaterial, MaterialBase* gndGridMaterial, MaterialBase* gndSurfaceMaterial) {
	this->voxelScene = &voxelScene;	
	this->defaultBlockMaterial = defaultBlockMaterial;
	this->groundGridMaterial = gndGridMaterial;
	this->groundSurfaceMaterial = gndSurfaceMaterial;
}


void Renderer::Prepare(void) {

	MaterialsMap* mats = MaterialLibrary::GetInstance().GetMaterialsMap();
	
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
	
	// simple render commands second, because they can contain transparent materials
	DoSimpleCommands();

	// voxel ground, which is actually part of the voxel scene, last
	if (voxelScene) {
		DoVoxelSceneGround();
	}


	if (camera->GetViewProjectionMatrixIsDirty() == true) {
		camera->ResetDirtyState();		
	}

}

//TODO: Make Sorting a separate public method!
void Renderer::SortSimpleCommands(void) {
	
	std::sort(renderCommands.begin(), renderCommands.end(),
		[](const std::unique_ptr<RenderCommand>& a, const std::unique_ptr<RenderCommand>& b) -> bool {
			
			//super simple sorting which puts transparent materials at the end
			return a->GetMaterial()->GetTransparent() < b->GetMaterial()->GetTransparent();
		});

}


void Renderer::DoSimpleCommands(void) {
	
	for (unsigned int i = 0; i < renderCommands.size(); ++i) {
		RenderCommand* command = renderCommands[i].get();		

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
			MaterialBase* material = MaterialLibrary::GetInstance().GetMaterial(materialId);
			
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


void Renderer::DoVoxelSceneGround(void) {
	if (groundSurfaceMaterial != nullptr) {
		groundSurfaceMaterial->Bind();
		groundSurfaceMaterial->SetModelMatrixUniform(glm::mat4(1.0f));

		if (camera->GetViewProjectionMatrixIsDirty()) {
			groundSurfaceMaterial->SetViewProjectionMatrixUniform(camera->GetViewProjectionMatrix());
		}

		voxelScene->GetGround().GetMeshes()[1].Draw();
		groundSurfaceMaterial->Unbind();
	}

	if (groundGridMaterial != nullptr) {
		groundGridMaterial->Bind();
		groundGridMaterial->SetModelMatrixUniform(glm::mat4(1.0f));

		if (camera->GetViewProjectionMatrixIsDirty()) {
			groundGridMaterial->SetViewProjectionMatrixUniform(camera->GetViewProjectionMatrix());
			if (groundGridMaterial->GetAffectedByLight()) {
				groundGridMaterial->SetViewPosUniform(camera->GetPosition());
			}
		}

		voxelScene->GetGround().GetMeshes()[0].Draw();
		groundGridMaterial->Unbind();
	}
}


void Renderer::CalculateViewport(const glm::vec2& rect) {
	glViewport(0, 0, static_cast<GLsizei>(rect.x), static_cast<GLsizei>(rect.y));
}


