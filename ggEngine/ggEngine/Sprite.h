#pragma once
#include "DrawObject.h"
#include "SpriteInfo.h"
#include "ConstantEnum.h"
#include <d3d9.h>
#include <string>
#include "Matrix.h"
#include "SpriteType.h"
namespace ggEngine {
	class Body;
	class Sprite :public DrawObject {
	public:
		Sprite(DrawManager *drawManager, SpriteInfo *image);
		Sprite(DrawManager *drawManager);
		~Sprite();
		virtual void Draw(Matrix translatedWorldMatrix);
		virtual void SetWidth(float width);
		virtual void SetHeight(float height);
		virtual float GetWidth();
		virtual float GetHeight();
		void SetImage(SpriteInfo *image);
		void Destroy();
		void Destroy(bool isClearCache);
		SpriteInfo* GetImage() { return this->image; }
		virtual void SetScale(float x, float y);
		virtual void SetScale(Vector vector);
		void SetBody(Body* body) { this->body = body; }
		Body* GetBody() { return this->body; }
		int GetOpacity() { return this->opacity; }
		void SetOpacity(int opacity) { this->opacity = opacity%256; }
	protected:
		SpriteInfo *image = nullptr;
		int opacity = 255;
	};
}