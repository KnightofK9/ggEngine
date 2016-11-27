#pragma once
namespace ggEngine{
	struct Direction {
		bool none = false;
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		void Reset() {
			none = false;
			up = false;
			down = false;
			left = false;
			right = false;
		}
		bool Any() {
			return left || right || up || down;
		}
		void Revert() {
			up = !up;
			down = !down;
			left = !left;
			right = !right;
		}
	};
}