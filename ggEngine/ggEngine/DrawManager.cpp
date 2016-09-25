#include "DrawManager.h"
#include "Group.h"
#include "Sprite.h"
#include "Texture.h"
#include "Game.h"
#include "State.h"
#include "StateManager.h"
namespace ggEngine {
	DrawManager::DrawManager(Game* game)
	{
		this->stateManager = game->stateManager;
		this->device = &game->GetD3DManager()->getDevice();
	}
	Sprite* DrawManager::CreateSprite(std::string fileSource){
		return new Sprite(this->device, fileSource);
	}
	DrawManager::~DrawManager()
	{
		Destroy();
	}

	void DrawManager::Destroy()
	{
		
	}

	void DrawManager::Render2D()
	{
		Update2D();
	}

	void DrawManager::DrawObjectFromGroup(std::list<Group*> groupList)
	{
		for (std::list<Group*>::iterator it = groupList.begin(); it != groupList.end(); ++it) {
			DrawList((*it)->GetDrawList());
			DrawObjectFromGroup((*it)->GetGroupList());
		}
	}

	void DrawManager::DrawList(std::list<DrawObject*> *drawObjectList)
	{
		for (std::list<DrawObject*>::iterator it = drawObjectList->begin(); it != drawObjectList->end();) {
			if ((*it)->IsAlive()) {
				(*it)->Draw();
				++it;
			}
			else {
				std::list<DrawObject*>::iterator tempIt = it;
				++it;
				delete (*tempIt);
				drawObjectList->erase(tempIt);
			}
		}
	}


	void DrawManager::Update2D()
	{
		State* state = this->stateManager->GetCurrentState();
		state->PreRender();
		DrawObjectFromGroup(state->GetGroupList());
		DrawObjectFromGroup(this->topGroupList);
	}

}