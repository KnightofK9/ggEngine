#pragma once
#include "DrawObject.h"
#include "Texture.h"
#include "ConstantEnum.h"
#include <d3d9.h>
#include <string>
#include "Matrix.h"
namespace ggEngine {
	class Body;
	class Sprite :public DrawObject {
	public:
		Sprite(LPDIRECT3DDEVICE9 device, std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
		Sprite(LPDIRECT3DDEVICE9 device, Texture *image);
		~Sprite();
		virtual void Draw();
		virtual void Draw(Matrix translatedWorldMatrix);
		virtual void SetWidth(float width);
		virtual void SetHeight(float height);
		virtual float GetWidth();
		virtual float GetHeight();
		void SetImage(Texture *image);
		void Destroy();
		void Destroy(bool isClearCache);
		Texture* GetImage() { return this->image; }
		virtual void SetScale(float x, float y);
		void Transform();
		void Transform(Matrix translatedWorldMatrix);
		void SetAnchor(float x, float y) { this->anchor.x = x;this->anchor.y = y; }
		Vector GetAnchor() { return this->anchor; }
		void SetBody(Body* body) { this->body = body; }
		Body* GetBody() { return this->body; }
		Body* body;
		LPD3DXSPRITE GetSpriteHandle() { return this->spriteHandle; }
	protected:
		Sprite(LPDIRECT3DDEVICE9 device);
		Texture *image;
		LPD3DXSPRITE spriteHandle;
		float width;
		float height;
		Vector anchor;
	};
}