#pragma once
#include "GGObject.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "ConstantEnum.h"
#include "Game.h"
namespace ggEngine {
	class DrawManager:public GGObject{
	public:
		DrawManager();
		~DrawManager();
		void Destroy();
		void Render2D();
		LPD3DXSPRITE getSpriteHandler() { return this->spriteHandler; }
	private:
		void Update2D();
		LPD3DXSPRITE spriteHandler;
	};
}