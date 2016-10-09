#pragma once
#include "EventArg.h"
#include "Vector.h"
#include "Direction.h"
namespace ggEngine {
	class GameObject;
	class ColliderArg :public EventArg {
	public:
		ColliderArg();
		~ColliderArg();
		bool overLapped = false;
		bool bound = false;
		float remainingTime = 0;
		Vector normalSurfaceVector;
		Direction blockDirection;
		GameObject *colliderObject;
	};
}