#include "TimeBasedEventManager.h"
#include "TimeBasedEventInfo.h"
namespace ggEngine {
	TimeBasedEventManager::TimeBasedEventManager(Game * game)
	{
		this->game = game;
	}
	void TimeBasedEventManager::Update(double deltaTimeInMs)
	{
		for (auto it = this->timeBasedEventList.begin(); it != this->timeBasedEventList.end(); ) {
			if ((*it)->isFinished) {
				auto temp = it;
				++it;
				delete *temp;
				this->timeBasedEventList.remove(*temp);
				continue;
			}
			if ((*it)->isAllowToPlay) {
				(*it)->currentTime += deltaTimeInMs;
				if ((*it)->currentTime >= (*it)->delay) {
					(*it)->function();
					switch ((*it)->type) {
					case TimeBasedEvent_Single:
						(*it)->isFinished = true;
						break;
					case TimeBasedEvent_Loop:
						(*it)->numberOfLoops--;
						if ((*it)->numberOfLoops <= 0) {
							(*it)->isFinished = true;
						}
						else (*it)->currentTime -= (*it)->delay;
						break;
					case TimeBasedEvent_LoopInfinity:
						(*it)->currentTime = 0;
						break;
					}
				}
			}
			++it;
		}
	}
	void TimeBasedEventManager::Reset()
	{
		this->timeBasedEventList.clear();
	}
	void TimeBasedEventManager::AddEvent(TimeBasedEventInfo * e)
	{
		this->timeBasedEventList.push_back(e);
	}
}
