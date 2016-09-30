#pragma once
#include "GGObject.h"
#include <functional>
#include "KeyBoardEventArg.h"
#include "MouseEventArg.h"
namespace ggEngine {
	class Game;
	class GameObject;
	class Events :public GGObject {
	public:
		Events(Game *game,GameObject *go);
		~Events();
		void Destroy();
		std::function<void(KeyBoardEventArg)> onKeyDown;
		std::function<void(KeyBoardEventArg)> onKeyUp;
		std::function<void(MouseEventArg)> onMousePress;
	private:
		Game *game;
		GameObject *go;
	};
}