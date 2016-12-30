#include "CameraActiveGroup.h"
#include "Game.h"
#include "Camera.h"
#include "Body.h"
namespace ggEngine {
	CameraActiveGroup::CameraActiveGroup(Game * game) : Group(game)
	{
		this->camera = game->camera;
	}
	CameraActiveGroup::~CameraActiveGroup()
	{
	}
	void CameraActiveGroup::Update()
	{
		this->activeGameObjectList.clear();
		Rect r = this->camera->GetNormalRect();
		for (auto it = this->drawList.begin(); it != this->drawList.end(); ++it) {
			GameObject* go = (*it);
			//if (!go->IsAlive()) continue;
			Rect r2 = go->body->GetRect();
			Rect i;
			if (Rect::intersect(i, r2, r)) {
				if (go->events != nullptr) {
					if (!go->events->wasInCamera) {
						if (go->events->onEnterCamera != nullptr) {
							EventArg e;
							go->events->onEnterCamera(go, e);
						}
					}
					go->events->wasInCamera = true;
				}
				this->activeGameObjectList.push_back(go);
			}
			else {
				if (go->events != nullptr) {
					if (go->events->wasInCamera) {
						if (go->events->onOutOfCamera != nullptr) {
							EventArg e;
							go->events->onOutOfCamera(go, e);
						}
					}
					go->events->wasInCamera = false;
				}

			}
		}
		Group::Update();
	}
	void CameraActiveGroup::UpdatePhysics()
	{
		for (auto it = this->activeGameObjectList.begin(); it != this->activeGameObjectList.end(); ++it) {
			if ((*it)->IsAlive()) {
				if ((*it)->body != nullptr && (*it)->body->IsEnable()) {
					(*it)->body->Update();
				}
			}
		}
		for (auto it = this->groupList.begin(); it != this->groupList.end(); ++it) {
			if ((*it)->IsAlive()) {
				(*it)->UpdatePhysics();
			}
		}
	}
	void CameraActiveGroup::Draw()
	{
		this->UpdateWorldPosition();
		if ((this)->IsVisible()) {
			this->drawManager->DrawList(this->activeGameObjectList, this->isUsedMask);
			for (auto it = this->groupList.begin(); it != this->groupList.end();++it) {
				(*it)->Draw();
			}
		}
	}
	std::list<GameObject*> CameraActiveGroup::GetDrawList()
	{
		return this->activeGameObjectList;
	}
}
