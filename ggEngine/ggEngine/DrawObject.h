#pragma once
#include "GameObject.h"
#include <d3dx9.h>
#include "Matrix.h"
namespace ggEngine {
	class DrawObject:public GameObject {
	public:
		virtual void Draw() = 0;
		virtual void Draw(Matrix translatedWorldMatrix) = 0;
	};
}