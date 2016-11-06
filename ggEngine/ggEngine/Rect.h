#pragma once
#include <algorithm>
using namespace std;
namespace ggEngine {
	class Rect {
	public:
		Rect(double l, double t, double r, double b) :
			left(l), top(t), right(r), bottom(b)
		{}
		Rect() {
			left = top = right = bottom = 0;
		}
		double left, top, right, bottom;
		// Determine if rectangles r1 and r2 intersect. So they do,
		// return true and set "result" to the intersection. If they
		// don't then return false and "result" is undefined.
		static bool intersect(Rect &result, const Rect &r1, const Rect &r2)
		{
			result.top = max(r1.top, r2.top);
			result.bottom = min(r1.bottom, r2.bottom);
			result.left = max(r1.left, r2.left);
			result.right = min(r1.right, r2.right);
			return (result.top < result.bottom && result.left < result.right);
		}


	};

}