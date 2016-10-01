#pragma once
#include "EventArg.h"
#include "Vector.h"
#include "Direction.h"
namespace ggEngine {
	class ColliderArg :public EventArg {
	public:
		ColliderArg();
		~ColliderArg();
		bool overLapped = false;
		bool bound = false;
		Vector normalSurfaceVector;
		Direction blockDirection;
	};
}