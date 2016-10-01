#pragma once
namespace ggEngine{
	struct Direction {
		bool none = false;
		bool any = false;
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		void Reset() {
			none = false;
			any = false;
			up = false;
			down = false;
			left = false;
			right = false;
		}
	};
}