#pragma once
#include "GGObject.h"
#include <list>
//#include <claw/tween/easing/easing_linear.hpp>
//#include <claw/tween/single_tweener.hpp>
//#include <claw/tween/tweener_group.hpp>
namespace ggEngine {
	class Tween;
	class Game;
	class TweenManager : public GGObject {
	public:
		TweenManager(Game *game);
		~TweenManager();
		void Update(double deltaTime);
		void AddTween(Tween* tween);
	private:
		Game *game;
		std::list<Tween*> tweenerList;
	};
}