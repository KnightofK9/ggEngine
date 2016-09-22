#include "Sprite.h"

namespace ggEngine {
	Sprite::Sprite(LPDIRECT3DDEVICE9 device, std::string filename, D3DCOLOR transcolor)
	{
		this->image = new Texture(device, filename, transcolor);
		if (image->GetTexture() == NULL) {
			SetImage(new Texture(device, "default.bmp", transcolor));
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
