#include "Timer.h"

namespace ggEngine {
	Timer::Timer(void)
	{
		timerStart = timeGetTime();
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
	bool Timer::stopwatch(int ms)
	{
		if (timeGetTime() > stopwatchStart + ms) {
			stopwatchStart = getTimer();
			return true;
		}
		else return false;
	}
}