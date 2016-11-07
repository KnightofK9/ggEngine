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
		double remainingTime = 0;
		double entryTime = 1;
		Vector normalSurfaceVector;
		Direction blockDirection;
		Vector currentVelocity;
		GameObject *colliderObject;
		void Reset() {
			overLapped = false;
			bound = false;
			remainingTime = 0;
			entryTime = 1;
			blockDirection.Reset();
			colliderObject = nullptr;
		}
	};
}