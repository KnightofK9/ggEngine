#include "Scene.h"
#include "Group.h"
#include "Add.h"
#include "Preload.h"
#include "DrawManager.h"
namespace ggEngine{
	Scene::Scene(DrawManager *drawManager){
		this->drawManager = drawManager;
	}
	Scene::~Scene(){
		Destroy();
	}
	void Scene::Start()
	{
		Init();
	}
	void Scene::Destroy(){

	}
}