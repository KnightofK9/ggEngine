#pragma once
#include "GGObject.h"
#include <list>
#include <map>
namespace ggEngine {
	class GameObject;
	class Game;
	class CameraEventManager : public GGObject {
	public:
		CameraEventManager(Game *game);
		~CameraEventManager();
		void RemoveTracking(GameObject *go);
		void Track(GameObject *go);
		void Update();
		void Reset();
	private:
		bool IsTracking(GameObject *go);
		Game* game;
		std::map<GameObject*, bool> trackingListCameraMap;
		std::list<GameObject*> gameObjectList;
	};
}