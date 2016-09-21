#pragma once
#include "GameObject.h"
#include <d3dx9.h>
namespace ggEngine {
	class DrawObject:public GameObject {
	public:
		virtual void Draw() {}
	};
}