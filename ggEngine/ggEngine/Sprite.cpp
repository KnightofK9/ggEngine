#include "Sprite.h"
#include "Body.h"


namespace ggEngine {
	Sprite::Sprite(Game *game, SpriteInfo * image) : GameObject(game)
	{
		SetImage(image);
		this->anchor = Vector(0, 0);
		this->body = NULL;
		this->color = D3DCOLOR_XRGB(255, 255, 255);
		this->style = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
	}

	Sprite::Sprite(Game *game) : GameObject(game)
	{
		this->color = D3DCOLOR_XRGB(255, 255, 255);
		this->body = NULL;
		this->anchor = Vector(0.5, 0.5);
		this->style = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
	}

	Sprite::~Sprite()
	{
		//g_debug.Log("Deleting Sprite");

	}
	void Sprite::Draw()
	{
		if (!visible) return;
		Transform(spriteHandle);
		RECT srcRect = image->GetRect();
		color = (color & 0x00FFFFFF) | (opacity << 24);
		if (spriteHandle->Begin(style) == D3D_OK)
		{
			spriteHandle->Draw(this->GetImage()->GetTexture()->GetDxTexture(), &srcRect, NULL, NULL, color);
			spriteHandle->End();
		}
	}
	void Sprite::DrawRect()
	{
		Transform(spriteHandle);
		RECT srcRect = image->GetRect();
		if (!visible) return;
		RECT drawRect = Helper::intersectRectAndGroup(srcRect, this, this->parentGroup);
		color = (color & 0x00FFFFFF) | (opacity << 24);
		if (spriteHandle->Begin(style) == D3D_OK)
		{
			spriteHandle->Draw(this->GetImage()->GetTexture()->GetDxTexture(), &drawRect, NULL, NULL, color);
			spriteHandle->End();
		}
	}
	

	void Sprite::SetImage(SpriteInfo *image)
	{
		this->image = image;
		this->width =  image->GetWidth();
		this->height =  image->GetHeight();
	}
	void Sprite::SetScale(double x, double y)
	{
		this->scale = Vector(x, y);
		this->width = this->image->GetWidth()*x;
		this->height = this->image->GetHeight()*y;
	}
	void Sprite::SetScale(Vector vector)
	{
		SetScale(vector.x, vector.y);
	}
	void Sprite::SetWidth(double width)
	{
		this->scale.x = (double)width / this->image->GetWidth();
		this->width = width;
	}
	double Sprite::GetWidth()
	{
		//return this->image->GetWidth()*this->scale.x;
		return this->width;
	}
	void Sprite::SetHeight(double height)
	{
		this->scale.y = (double)height / this->image->GetHeight();
		this->height = height;
	}
	double Sprite::GetHeight()
	{
		//return this->image->GetHeight()*this->scale.y;
		return this->height;
	}
	
}
