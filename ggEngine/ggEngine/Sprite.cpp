#include "Sprite.h"

namespace ggEngine {
	Sprite::Sprite(LPDIRECT3DDEVICE9 device)
	{
		HRESULT result = D3DXCreateSprite(device, &this->spriteHandle);
		if (result != D3D_OK)
		{
			this->spriteHandle = NULL;
			throw ERROR_CODE_FAIL_INIT_SPRITE_HANDLER;
		}
	}
	Sprite::Sprite(LPDIRECT3DDEVICE9 device, std::string filename, D3DCOLOR transcolor)
	{
		this->image = new Texture(device, filename, transcolor);
		this->width = image->GetWidth();
		this->height = image->GetHeight();
		if (image->GetTexture() == NULL) {
			SetImage(new Texture(device, "default.bmp", transcolor));
		}
		HRESULT result = D3DXCreateSprite(device, &this->spriteHandle);
		if (result != D3D_OK)
		{
			this->spriteHandle = NULL;
			throw ERROR_CODE_FAIL_INIT_SPRITE_HANDLER;
		}
	}
	Sprite::Sprite(LPDIRECT3DDEVICE9 device, Texture * image)
	{
		SetImage(image);
		HRESULT result = D3DXCreateSprite(device, &this->spriteHandle);
		if (result != D3D_OK)
		{
			this->spriteHandle = NULL;
			throw ERROR_CODE_FAIL_INIT_SPRITE_HANDLER;
		}
	}
	Sprite::~Sprite()
	{
	}
	void Sprite::Draw()
	{
		Transform();
		RECT srcRect = { 0, 0, this->image->GetWidth(), this->image->GetHeight() };
		if (this->spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			this->spriteHandle->Draw(this->GetImage()->GetTexture(), &srcRect, NULL, NULL, D3DXCOLOR(255, 255, 255, 255));
			spriteHandle->End();
		}
	}
	void Sprite::Destroy()
	{
		this->alive = false;
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
	void Sprite::SetScale(float x, float y)
	{
		GameObject::SetScale(x, y);
		this->width *= x;
		this->height *= y;
	}
	void Sprite::SetWidth(int width)
	{
		this->scale.x = (float)width / this->image->GetWidth();
		this->width = width;
	}
	int Sprite::GetWidth()
	{
		return this->image->GetWidth()*this->scale.x;
	}
	void Sprite::SetHeight(int height)
	{
		this->scale.y = (float)height / this->image->GetHeight();
		this->height = height;
	}
	int Sprite::GetHeight()
	{
		return this->image->GetHeight()*this->scale.y;
	}
	void Sprite::Transform(){
		D3DXMATRIX mat;
		Vector scaleTransform(this->scale.x, this->scale.y);
		Vector rotateCenter((this->width) / 2, (this->height) / 2);
		//Vector scaleCenter((this->width) / 2, (this->height) / 2);
		Vector trans(this->position.x - this->width*(this->anchor.x), this->position.y - this->height*(this->anchor.y));
		D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &rotateCenter, this->rotate, &trans);
		this->spriteHandle->SetTransform(&mat);
	}
}
