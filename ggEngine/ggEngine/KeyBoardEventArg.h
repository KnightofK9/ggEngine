#pragma once
#include "EventArg.h"
namespace ggEngine {
	class KeyBoardEventArg :public EventArg {
	public:
		char* keyState;
		int isPress(int keyCode) {
			return keyState[keyCode] & 0x80;
		}
	};
}