#include "CameraEventManager.h"
#include "Rect.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"
#include "Body.h"
#include "Game.h"
#include "EventManager.h"
ggEngine::CameraEventManager::CameraEventManager(Game * game)
{
	this->game = game;
	this->trackingListCameraMap = &game->eventManager->trackingListCameraMap;
}
ggEngine::CameraEventManager::~CameraEventManager()
{
}

void ggEngine::CameraEventManager::Track(GameObject * go)
{
	Rect cameraRect = this->game->camera->GetNormalRect();
	Rect ojectRect = (go)->GetRect();
	Rect r;
	bool isInCamera = Rect::intersect(r, cameraRect, ojectRect);
	(*this->trackingListCameraMap)[go] = isInCamera;
}
void ggEngine::CameraEventManager::Update(double dt)
{
	Rect cameraRect = this->game->camera->GetNormalRect();
	for (auto it = this->trackingListCameraMap->begin(); it != this->trackingListCameraMap->end();++it) {
		GameObject *gameObject = (*it).first;
		if (!gameObject->IsAlive()) continue;
		Rect ojectRect = gameObject->GetRect();
		Rect r;
		bool wasInCamera = (*it).second;
		bool isInCamera = Rect::intersect(r, cameraRect, ojectRect);
		EventArg e;
		if (isInCamera == !wasInCamera) {
			(*it).second = isInCamera;
			if (isInCamera) {
				if (gameObject->events->onEnterCamera != nullptr) {
					gameObject->events->onEnterCamera(gameObject, e);
				}
			}
			else {
				if (gameObject->events->onOutOfCamera != nullptr) {
					gameObject->events->onOutOfCamera(gameObject, e);
				}
			}
		}	
	}
}

void ggEngine::CameraEventManager::Reset()
{
	this->trackingListCameraMap->clear();
}
