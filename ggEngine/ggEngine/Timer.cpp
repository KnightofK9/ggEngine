#include "Timer.h"
#include "DebugDefine.h"
namespace ggEngine {
	Timer::Timer(void)
	{
		timerStart = timeGetTime();
		timerGetDelta = timerStart;
		reset();
	}
	Timer::~Timer(void)
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
	double Timer::getDeltaTime()
	{
#ifdef DEBUG_FRAME
		return (double)14.4 / 1000;
#else
		return (double)deltaTime / 1000;
#endif
	}
	double Timer::getDeltaTimeInMilisecond()
	{
#ifdef DEBUG_FRAME
		return 14.4;
#else
		return (double)deltaTime;
#endif
	}
	void Timer::updateDeltaTime()
	{
		deltaTime = getTimer() - timerGetDelta;
		timerGetDelta = getTimer();
	}
}