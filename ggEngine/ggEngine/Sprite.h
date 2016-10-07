#pragma once
#include "DrawObject.h"
#include "Texture.h"
#include "ConstantEnum.h"
#include <d3d9.h>
#include <string>
#include "Matrix.h"
namespace ggEngine {
	enum SpriteType { SpriteType_Texture, SpriteType_Atlas};
	class Body;
	class Sprite :public DrawObject {
	public:
		Sprite(DrawManager *drawManager, std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
		Sprite(DrawManager *drawManager, Texture *atlas, RECT atlasRect);
		Sprite(DrawManager *drawManager,Texture *image);
		Sprite(DrawManager *drawManager);
		~Sprite();
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
		virtual void SetScale(Vector vector);
		void SetBody(Body* body) { this->body = body; }
		Body* GetBody() { return this->body; }
		int GetOpacity() { return this->opacity; }
		void SetOpacity(int opacity) { this->opacity = opacity%256; }
		SpriteType type;
	protected:
		float orgWidth;
		float orgHeight;
		RECT atlasRect;
		Texture *image = nullptr;
		int opacity = 255;
	};
}