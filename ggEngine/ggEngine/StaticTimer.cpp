#include "StaticTimer.h"

namespace ggEngine {
	StaticTimer::StaticTimer() {
		SetTime(0);
	}
	StaticTimer::~StaticTimer(void)
	{
	}
	void StaticTimer::SetTime(DWORD currentTime)
	{
		this->currentTime = currentTime;
	}
	void StaticTimer::SetDelta(DWORD dt)
	{
		this->dt = dt;
	}
	bool StaticTimer::StopWatch(DWORD ms)
	{
		this->currentTime += this->dt;
		this->dt = 0;
		if (currentTime >  ms) {
			this->currentTime -= ms;
			return true;
		}
		return false;
	}
}