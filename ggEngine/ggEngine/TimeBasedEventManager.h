#pragma once
#include "GGObject.h"
#include <list>
#include <functional>
namespace ggEngine {
	class Game;
	class TimeBasedEventInfo;
	class TimeBasedEventManager : public GGObject {
	public:
		TimeBasedEventManager(Game *game);
		void Update(double deltaTimeInMs);
		void Reset();
		void AddEvent(TimeBasedEventInfo *e);
	private:
		std::list<TimeBasedEventInfo*> timeBasedEventList;
		Game *game;
	};
}