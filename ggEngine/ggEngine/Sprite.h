#pragma once
#include "DrawObject.h"
#include "Texture.h"
#include "ConstantEnum.h"
#include <d3d9.h>
#include <string>
namespace ggEngine {
	class Body;
	class Sprite :public DrawObject {
	public:
		Sprite(LPDIRECT3DDEVICE9 device, std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
		Sprite(LPDIRECT3DDEVICE9 device, Texture *image);
		~Sprite();
		virtual void Draw();
		virtual void SetWidth(int width);
		virtual void SetHeight(int height);
		virtual int GetWidth();
		virtual int GetHeight();
		void SetImage(Texture *image);
		void Destroy();
		void Destroy(bool isClearCache);
		Texture* GetImage() { return this->image; }
		void SetScale(float x, float y);
		void Transform();
		void SetAnchor(float x, float y) { this->anchor.x = x;this->anchor.y = y; }
		Vector GetAnchor() { return this->anchor; }
		void SetBody(Body* body) { this->body = body; }
		Body* GetBody() { return this->body; }
	protected:
		Body* body;
		Sprite(LPDIRECT3DDEVICE9 device);
		Texture *image;
		LPD3DXSPRITE spriteHandle;
		int width;
		int height;
		Vector anchor;
	};
}