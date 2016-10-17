#pragma once
#include "GameObject.h"
#include <d3dx9.h>
#include "Matrix.h"
#include "DrawManager.h"
namespace ggEngine {
	class DrawObject:public GameObject {
	public:
		DrawObject(DrawManager *DrawManager);
		~DrawObject();
		virtual void Draw() = 0;
	protected:
		DrawManager *drawManager;
		LPD3DXSPRITE spriteHandle;
	};
}