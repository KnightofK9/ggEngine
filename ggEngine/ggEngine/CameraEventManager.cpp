#include "CameraEventManager.h"
#include "Rect.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"
ggEngine::CameraEventManager::CameraEventManager(Game * game)
{
	this->game = game;
}
ggEngine::CameraEventManager::~CameraEventManager()
{
}
void ggEngine::CameraEventManager::RemoveTracking(GameObject * go)
{
	this->trackingListCameraMap.erase(go);
	this->gameObjectList.remove(go);
}
void ggEngine::CameraEventManager::Track(GameObject * go)
{
	this->gameObjectList.push_back(go);
}
void ggEngine::CameraEventManager::Update()
{
	Rect cameraRect = this->game->camera->GetNormalRect();
	for (auto it = this->gameObjectList.begin(); it != this->gameObjectList.end();++it) {
		Rect ojectRect = (*it)->GetRect();
		Rect r;
		bool isInCamera = Rect::intersect(r, cameraRect, ojectRect);
		EventArg e;
		bool isTracking = IsTracking(*it);
		if (isInCamera) {
			if (!isTracking) {
				this->trackingListCameraMap[*it] = true;
				return;
			}
			if (isInCamera = !isTracking && (*it)->events->onEnterCamera != nullptr) {
				isTracking = isInCamera;
				(*it)->events->onEnterCamera(*it,e);
			}
		}
		else {
			if (!isTracking) {
				this->trackingListCameraMap[*it] = false;
				return;
			}
			if (isInCamera = !isTracking && (*it)->events->onOutOfCamera != nullptr) {
				isTracking = isInCamera;
				(*it)->events->onOutOfCamera(*it, e);
			}
		}
	}
}

void ggEngine::CameraEventManager::Reset()
{
	this->trackingListCameraMap.clear();
	this->gameObjectList.clear();
}

bool ggEngine::CameraEventManager::IsTracking(GameObject * go)
{
	auto it = this->trackingListCameraMap.find(go);
	bool isFound = false;
	if (it != this->trackingListCameraMap.end())
	{
		isFound = true;
	}
	return isFound;
}
