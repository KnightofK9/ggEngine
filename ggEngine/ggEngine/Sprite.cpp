#include "Sprite.h"

namespace ggEngine {
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
			throw ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW;
		}
	}
	Sprite::Sprite(LPDIRECT3DDEVICE9 device, Texture * image)
	{
		SetImage(image);
		HRESULT result = D3DXCreateSprite(device, &this->spriteHandle);
		if (result != D3D_OK)
		{
			this->spriteHandle = NULL;
			throw ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW;
		}
	}
	Sprite::~Sprite()
	{
		Destroy();
	}
	void Sprite::Draw()
	{
		RECT srcRect = { 0, 0, this->GetWidth(), this->GetHeight() };		
		if (this->spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			this->spriteHandle->Draw(this->GetImage()->GetTexture(), &srcRect, NULL, NULL, D3DXCOLOR(255, 255, 255, 255));
			spriteHandle->End();
		}
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
	void Sprite::Transform(){
		D3DXMATRIX mat;
		Vector scaleTransform(this->scale.x, this->scale.y);
		Vector centerTransfrom((this->width*this->scale.x) / 2, (this->height*this->scale.y) / 2);
		Vector trans(this->position.x, this->position.y);
		D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &centerTransfrom, this->rotate, &trans);
		this->spriteHandle->SetTransform(&mat);
	}
}
