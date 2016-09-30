#pragma once
#include "GGObject.h"
#include "GameObject.h"
namespace ggEngine {
	class Game;
	class EventManager: public GGObject {
	public:
		EventManager(Game *game);
		~EventManager();
		void Destroy();
		void EnableInput(GameObject *go);
	private:
		Game *game;
	};
}