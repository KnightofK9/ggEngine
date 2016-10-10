#pragma once
#include <claw.hpp>
#include "GGObject.h"
//#include <tween/easing/easing_linear.hpp>
//#include <tween/single_tweener.hpp>
//#include <tween/tweener_group.hpp>
namespace ggEngine {
	class Game;
	class TweenManager : public GGObject {
	public:
		TweenManager(Game *game);
		void Update();
		~TweenManager();
	private:
		Game *game;
	};
}