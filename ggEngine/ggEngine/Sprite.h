#pragma once
#include "DrawObject.h"
#include "Texture.h"
#include "ConstantEnum.h"
#include <string>
namespace ggEngine {
	class Sprite :public DrawObject {
	public:
		Sprite(std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
		Sprite(Texture *image);
		~Sprite();
		void Draw();
		void Destroy();
		void Destroy(bool isClearCache);
		Texture* GetImage() { return this->image; }
		void SetImage(Texture *image);
		void SetWidth(int width) { this->width = width; }
		int GetWidth() { return this->width; }
		void SetHeight(int height) { this->height = height; }
		int GetHeight() { return this->height; }
	private:
		Texture *image;
		int width;
		int height;
	};
}