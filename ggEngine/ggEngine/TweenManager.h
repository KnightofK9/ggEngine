#pragma once
#include "GGObject.h"
#include <claw/tween/easing/easing_linear.hpp>
#include <claw/tween/single_tweener.hpp>
#include <claw/tween/tweener_group.hpp>
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