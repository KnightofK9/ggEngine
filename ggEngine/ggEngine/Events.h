#pragma once
#include "GGObject.h"
#include <functional>
#include "KeyBoardEventArg.h"
#include "MouseEventArg.h"
#include "ColliderArg.h"
namespace ggEngine {
	class Game;
	class GameObject;
	class Events :public GGObject {
	public:
		Events(Game *game,GameObject *go);
		~Events();
		void Destroy();
		std::function<void(GameObject*, KeyBoardEventArg)> onKeyDown;
		std::function<void(GameObject*, KeyBoardEventArg)> onKeyUp;
		std::function<void(GameObject*, MouseEventArg)> onMousePress;
		std::function<void(GameObject*, ColliderArg)> onWorldBounds;
		std::function<void(GameObject*, ColliderArg)> onCollide;
		std::function<void(GameObject*, ColliderArg)> onOverlap;
		std::function<void(GameObject*, EventArg)> onMoveComplete;
		std::function<void(GameObject*, EventArg)> movementCallback;
	private:
		Game *game;
		GameObject *go;
	};
}