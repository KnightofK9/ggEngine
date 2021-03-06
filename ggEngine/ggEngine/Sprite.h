#pragma once
#include "SpriteInfo.h"
#include "ConstantEnum.h"
#include <d3d9.h>
#include <string>
#include "Matrix.h"
#include "SpriteType.h"
#include "GameObject.h"
#include "Texture.h"
namespace ggEngine {
	class Body;
	class Game;
	class Sprite : public GameObject {
	public:
		Sprite(Game *game, SpriteInfo *image);
		Sprite(Game *game);
		virtual ~Sprite();
		virtual void Draw();
		virtual void DrawRect();
		virtual void SetWidth(double width);
		virtual void SetHeight(double height);
		virtual double GetWidth();
		virtual double GetHeight();
		void SetImage(SpriteInfo *image);
		SpriteInfo* GetImage() { return this->image; }
		virtual void SetScale(double x, double y);
		virtual void SetScale(Vector vector);
		void SetColorTint(int r, int g, int b) { this->color = D3DCOLOR_XRGB(r, g, b); }
		void SetColorTint(D3DCOLOR color) { this->color = color; }
		D3DCOLOR GetColorTint() { return this->color; }
		virtual double GetOrgWidth() { return this->image->GetWidth(); }
		virtual double GetOrgHeight() { return this->image->GetHeight(); }
		DWORD style;
	protected:
		D3DCOLOR color;
		SpriteInfo *image = nullptr;
	};
}