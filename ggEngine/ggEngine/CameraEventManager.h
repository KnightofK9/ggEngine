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
		virtual ~CameraEventManager();
		void Track(GameObject *go);
		void Update(double dt) override;
		void Reset() override;
	private:
		Game* game;
		std::map<GameObject*, bool> *trackingListCameraMap;
		
	};
}