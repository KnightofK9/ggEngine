#pragma once
#include "GGObject.h"
#include "GameObject.h"
#include <list>
namespace ggEngine {
	class Game;
	class SpriteAnimation;
	class EventManager: public GGObject {
	public:
		EventManager(Game *game);
		virtual ~EventManager();

		void RemoveEventFromAllManager(GameObject *go);


		void Destroy();
		void EnableKeyBoardInput(GameObject *go);
		void EnableSpriteAnimationEvent(SpriteAnimation *go);
		void EnableCameraEvent(GameObject *go);
		void DisableCameraEvent(GameObject *go);

		void DisableKeyBoardInput(GameObject *go,bool isClearEvent = false);
		void EnableMouseInput(GameObject *go);
		void DisableMouseInput(GameObject *go, bool isClearEvent = false);
		void DispatchKeyBoardEvent(char *keyStates);
		void DispatchMouseEvent(double mouseX, double mouseY, bool isPress); 
		char ScanToChar(DWORD scanCode) const;
		void Reset();


		std::map<GameObject*, bool> trackingListCameraMap;
	private:
		void InitEvents(GameObject *go);
		Game *game;
		std::list<GameObject*> receivedKeyBoardList;
		std::list<GameObject*> receivedMouseList;
	};
}