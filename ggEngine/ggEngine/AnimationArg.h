#pragma once
#include <string>
#include "EventArg.h"

namespace ggEngine {
	class Animator;
	class AnimationArg : public EventArg {
	public:
		std::string animationName = "";
		Animator *animator;
	};
}