#pragma once
#include "ComponentBase.h"
#include <list>
#include <map>
namespace ggEngine {
	class GameObject;
	class Game;
	class CameraEventManager : public ComponentBase {
	public:
		CameraEventManager(Game *game);
		~CameraEventManager();
		void RemoveTracking(GameObject *go);
		void Track(GameObject *go);
		void Update(double dt) override;
		void Reset() override;
	private:
		bool IsTracking(GameObject *go);
		Game* game;
		std::map<GameObject*, bool> trackingListCameraMap;
	};
}