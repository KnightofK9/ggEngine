#pragma once
#include <time.h>
#include <Windows.h>
#include "GGObject.h"
#pragma comment(lib,"winmm.lib")
namespace ggEngine {
	class StaticTimer :public GGObject {
	public:
		StaticTimer(void);
		~StaticTimer(void);
		void SetTime(DWORD currentTime);
		void SetDelta(DWORD dt);
		bool StopWatch(DWORD ms);
		
	private:
		DWORD currentTime;
		DWORD dt;
		
	};
}