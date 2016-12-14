#pragma once
#include "ComponentBase.h"
#include <list>
//#include <claw/tween/easing/easing_linear.hpp>
//#include <claw/tween/single_tweener.hpp>
//#include <claw/tween/tweener_group.hpp>
namespace ggEngine {
	class TweenBase;
	class Game;
	class TweenManager : public ComponentBase {
	public:
		TweenManager(Game *game);
		virtual ~TweenManager();
		void Update(double deltaTime);
		void AddTween(TweenBase* tween);
		void RemoveTween(TweenBase* tween);
		void Reset();
	private:
		Game *game;
		std::list<TweenBase*> tweenerList;
	};
}