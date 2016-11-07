#pragma once
#include "SpriteInfo.h"
#include "ConstantEnum.h"
#include <d3d9.h>
#include <string>
#include "Matrix.h"
#include "SpriteType.h"
#include "GameObject.h"
namespace ggEngine {
	class Body;
	class Sprite : public GameObject {
	public:
		Sprite(DrawManager *drawManager, SpriteInfo *image);
		Sprite(DrawManager *drawManager);
		~Sprite();
		virtual void Draw();
		virtual void SetWidth(double width);
		virtual void SetHeight(double height);
		virtual double GetWidth();
		virtual double GetHeight();
		void SetImage(SpriteInfo *image);
		void Destroy();
		void Destroy(bool isClearCache);
		SpriteInfo* GetImage() { return this->image; }
		virtual void SetScale(double x, double y);
		virtual void SetScale(Vector vector);
		int GetOpacity() { return this->opacity; }
		void SetOpacity(int opacity) { this->opacity = opacity%256; }
		void SetColorTint(int r, int g, int b) { this->color = D3DCOLOR_XRGB(r, g, b); }
		void SetColorTint(D3DCOLOR color) { this->color = color; }
		D3DCOLOR GetColorTint() { return this->color; }
		virtual double GetOrgWidth() { return this->image->GetWidth(); }
		virtual double GetOrgHeight() { return this->image->GetHeight(); }
	protected:
		D3DCOLOR color;
		SpriteInfo *image = nullptr;
		int opacity = 255;
	};
}