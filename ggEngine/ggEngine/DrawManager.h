#pragma once
#include "GGObject.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "ConstantEnum.h"

namespace ggEngine {
	class DrawManager:public GGObject{
	public:
		DrawManager(IDirect3DDevice9 *device);
		~DrawManager();
		void Destroy();
		void Render2D();
		LPD3DXSPRITE getSpriteHandler() { return this->spriteHandler; }
	private:
		void Update2D();
		LPD3DXSPRITE spriteHandler;
		IDirect3DDevice9 *device;
	};
}