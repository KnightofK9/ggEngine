#pragma once
#include "ComponentBase.h"
#include <list>
//#include <claw/tween/easing/easing_linear.hpp>
//#include <claw/tween/single_tweener.hpp>
//#include <claw/tween/tweener_group.hpp>
namespace ggEngine {
	class Tween;
	class Game;
	class TweenManager : public ComponentBase {
	public:
		TweenManager(Game *game);
		~TweenManager();
		void Update(double deltaTime);
		void AddTween(Tween* tween);
		void Reset();
	private:
		Game *game;
		std::list<Tween*> tweenerList;
	};
}