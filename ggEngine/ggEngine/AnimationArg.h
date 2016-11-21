#pragma once
#include <string>
#include "EventArg.h"
namespace ggEngine {
	class AnimationArg : public EventArg {
	public:
		std::string animationName = "";
	};
}