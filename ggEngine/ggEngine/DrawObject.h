#pragma once
#include "GameObject.h"
#include <d3dx9.h>
#include "Matrix.h"
namespace ggEngine {
	class DrawObject:public GameObject {
	public:
		virtual void Draw(Matrix translatedWorldMatrix, LPD3DXSPRITE spriteHandle) = 0;
	};
}