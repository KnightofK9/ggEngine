#pragma once
#include "EventArg.h"
#include "Vector.h"
#include "Direction.h"
#include "Box.h"
namespace ggEngine {
	class GameObject;
	class ColliderArg :public EventArg {
	public:
		ColliderArg();
		virtual ~ColliderArg();
		bool overLapped = false;
		bool bound = false;
		double remainingTime = 0;
		double entryTime = 1;
		Vector normalSurfaceVector;
		Direction blockDirection;
		Vector currentVelocity;
		GameObject *colliderObject;
		Box b;
		bool operator<(const ColliderArg& other) const
		{
			return entryTime < other.entryTime;
		}
		bool operator==(const ColliderArg& other) const
		{
			return entryTime == other.entryTime;
		}
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