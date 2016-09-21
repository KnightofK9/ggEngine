#include "Sprite.h"

namespace ggEngine {
	Sprite::Sprite(std::string filename, D3DCOLOR transcolor)
	{
		this->image = new Texture(filename, transcolor);
		if (image->GetTexture() == NULL) {
			SetImage(new Texture("default.bmp", transcolor));
			this->width = image->GetWidth();
			this->height = image->GetHeight();
		}
	}
	Sprite::Sprite(Texture * image)
	{
		SetImage(image);
		this->width = image->GetWidth();
		this->height = image->GetHeight();
	}
	Sprite::~Sprite()
	{
		Destroy();
	}
	void Sprite::Draw()
	{
	}
	void Sprite::Destroy()
	{
	}
	void Sprite::Destroy(bool isClearCache)
	{
		this->image->Destroy();
		Destroy();
	}
	void Sprite::SetImage(Texture *image)
	{
		this->image = image;
		this->width = image->GetWidth();
		this->height = image->GetHeight();
	}
}
