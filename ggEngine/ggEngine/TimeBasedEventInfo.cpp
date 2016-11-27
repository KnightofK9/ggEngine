#include "TimeBasedEventInfo.h"
namespace ggEngine {

	TimeBasedEventInfo * TimeBasedEventInfo::Pause()
	{
		this->isAllowToPlay = false;
		return this;
	}

	TimeBasedEventInfo * TimeBasedEventInfo::Resume()
	{
		this->isAllowToPlay = true;
		return this;
	}

	TimeBasedEventInfo * TimeBasedEventInfo::Stop()
	{
		this->isFinished = true;
		return this;
	}

	TimeBasedEventInfo * TimeBasedEventInfo::Start()
	{
		this->isAllowToPlay = true;
		return this;
	}
	void TimeBasedEventInfo::Destroy()
	{
		Stop();
	}
}
