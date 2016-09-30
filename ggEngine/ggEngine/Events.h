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
		std::function<void(KeyBoardEventArg)> *onKeyDown;
		std::function<void(KeyBoardEventArg)> *onKeyUp;
		std::function<void(MouseEventArg)> *onMousePress;
		std::function<void(ColliderArg)> *onWorldBounds;
		std::function<void(ColliderArg)> *onCollide;
		std::function<void(ColliderArg)> *onOverlap;
		std::function<void(EventArg)> *onMoveComplete;
		std::function<void(EventArg)> *movementCallback;
	private:
		Game *game;
		GameObject *go;
	};
}