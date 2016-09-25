#include "Timer.h"

namespace ggEngine {
	Timer::Timer(void)
	{
		timerStart = timeGetTime();
		timerGetDelta = timerStart;
		reset();
	}
	Timer::~Timer(void)
	{
		Destroy();
	}
	void Timer::Destroy()
	{
	}
	DWORD Timer::getTimer()
	{
		return (DWORD)timeGetTime();
	}
	DWORD Timer::getStartTimeMillis()
	{
		return (DWORD)(timeGetTime() - timerStart);
	}
	void Timer::sleep(int ms)
	{
		DWORD start = getTimer();
		while (start + ms > getTimer());
	}
	void Timer::reset()
	{
		stopwatchStart = getTimer();
	}
	void Timer::resetDelta()
	{
		timerGetDelta = getTimer();
	}
	bool Timer::stopwatch(int ms)
	{
		if (timeGetTime() > stopwatchStart + ms) {
			stopwatchStart = getTimer();
			return true;
		}
		else return false;
	}
	float Timer::getDeltaTime()
	{
		return (float)deltaTime/1000;
	}
	void Timer::updateDeltaTime()
	{
		deltaTime = getTimer() - timerGetDelta;
		timerGetDelta = getTimer();
	}
}