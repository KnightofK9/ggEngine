#pragma once
#include "DrawObject.h"
#include "Texture.h"
#include "ConstantEnum.h"
#include <d3d9.h>
#include <string>
namespace ggEngine {
	class Sprite :public DrawObject {
	public:
		Sprite(LPDIRECT3DDEVICE9 device, std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
		Sprite(LPDIRECT3DDEVICE9 device, Texture *image);
		~Sprite();
		void Draw();
		void Destroy();
		void Destroy(bool isClearCache);
		Texture* GetImage() { return this->image; }
		void SetImage(Texture *image);
		void SetScale(float x, float y);
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();
		void Transform();
		void SetAnchor(float x, float y) { this->anchor.x = x;this->anchor.y = y; }
		Vector GetAnchor() { return this->anchor; }
	private:
		Texture *image;
		LPD3DXSPRITE spriteHandle;
		int width;
		int height;
		Vector anchor;
	};
}