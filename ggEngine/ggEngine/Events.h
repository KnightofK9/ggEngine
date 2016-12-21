#pragma once
#include "GGObject.h"
#include <functional>
#include "KeyBoardEventArg.h"
#include "MouseEventArg.h"
#include "ColliderArg.h"
#include "AnimationArg.h"
namespace ggEngine {
	class Game;
	class GameObject;
	class Events :public GGObject {
	public:
		Events(Game *game,GameObject *go);
		virtual ~Events();
		std::function<void()> resetEvent;
		std::function<void(GameObject*, KeyBoardEventArg)> onKeyPress;
		std::function<void(GameObject*, MouseEventArg)> onMousePress;
		std::function<void(GameObject*, ColliderArg)> onWorldBounds;
		std::function<void(GameObject*, ColliderArg)> onCollide;
		std::function<bool(GameObject*, ColliderArg)> onCheckingCollide;
		std::function<void(GameObject*, ColliderArg)> onOverlap;
		std::function<void(GameObject*, EventArg)> onMoveComplete;
		std::function<void(GameObject*, EventArg)> movementCallback;
		std::function<void(GameObject*)> onUpdate;
		std::function<void(GameObject*, AnimationArg)> onAnimationCompleted;
		std::function<void(GameObject*, EventArg)> onOutOfCamera;
		std::function<void(GameObject*, EventArg)> onEnterCamera;
		std::function<void(GameObject*, AnimationArg)> onAnimationCallBack;
		std::function<void(GameObject*, EventArg)> onDestroy;



		bool enable;
	private:
		Game *game;
		GameObject *go;
	};
}