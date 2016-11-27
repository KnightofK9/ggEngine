#pragma once
#include "GGObject.h"
#include <functional>
namespace ggEngine {
	enum TimeBasedEventType {TimeBasedEvent_Single,TimeBasedEvent_Loop, TimeBasedEvent_LoopInfinity};
	class TimeBasedEventInfo : public GGObject {
	public:
		std::function<void(void)> function;
		unsigned int delay = 0;
		unsigned int currentTime = 0;
		bool isFinished = false;
		bool isAllowToPlay = false;
		TimeBasedEventType type;
		unsigned int numberOfLoops = 0;
		TimeBasedEventInfo* Pause();
		TimeBasedEventInfo* Resume();
		TimeBasedEventInfo* Stop();
		TimeBasedEventInfo* Start();
		void Destroy() override;
	};
}