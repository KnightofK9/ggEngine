#pragma once
#include "GGObject.h"
#include "GameObject.h"
#include <list>
namespace ggEngine {
	class Game;
	class EventManager: public GGObject {
	public:
		EventManager(Game *game);
		~EventManager();
		void Destroy();
		void EnableKeyBoardInput(GameObject *go);
		void DisableKeyBoardInput(GameObject *go,bool isClearEvent = false);
		void EnableMouseInput(GameObject *go);
		void DisableMouseInput(GameObject *go, bool isClearEvent = false);
		void DispatchKeyBoardEvent(char *keyStates);
		void DispatchMouseEvent(float mouseX, float mouseY, bool isPress); 
		char ScanToChar(DWORD scanCode) const;
	private:
		void InitEvents(GameObject *go);
		Game *game;
		std::list<GameObject*> receivedKeyBoardList;
		std::list<GameObject*> receivedMouseList;
	};
}