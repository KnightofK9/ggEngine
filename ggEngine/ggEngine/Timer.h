#pragma once
#include <time.h>
#include <Windows.h>
#include "GGObject.h"
#pragma comment(lib,"winmm.lib")
namespace ggEngine {
	class Timer:public GGObject {
	public:
		Timer(void);
		~Timer(void);
		void Destroy();
		DWORD getTimer();
		DWORD getStartTimeMillis();
		void sleep(int ms);
		void reset();
		void resetDelta();
		bool stopwatch(int ms);
		double getDeltaTime();
		void updateDeltaTime();
	private:
		DWORD timerStart;
		DWORD stopwatchStart;
		DWORD timerGetDelta;
		DWORD deltaTime;
	};
}