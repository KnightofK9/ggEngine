#include "Sprite.h"
#include "Body.h"
#include "Texture.h"
namespace ggEngine {
	Sprite::Sprite(DrawManager *drawManager, SpriteInfo * image) : DrawObject(drawManager)
	{
		SetImage(image);
		this->anchor = Vector(0.5, 0.5);
		this->body = NULL;
		this->color = D3DCOLOR_XRGB(255, 255, 255);
	}

	Sprite::Sprite(DrawManager* drawManager) : DrawObject(drawManager)
	{
		this->color = D3DCOLOR_XRGB(255, 255, 255);
	}

	Sprite::~Sprite()
	{
	}
	void Sprite::Draw(Matrix translatedWorldMatrix)
	{
		Transform(translatedWorldMatrix, spriteHandle);
		RECT srcRect = image->GetRect();
		if (!visible) return;
		color = (color & 0x00FFFFFF) | (opacity << 24);
		if (spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			spriteHandle->Draw(this->GetImage()->GetTexture()->GetDxTexture(), &srcRect, NULL, NULL, color);
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
	void Sprite::SetImage(SpriteInfo *image)
	{
		this->image = image;
		this->width =  image->GetWidth();
		this->height =  image->GetHeight();
	}
	void Sprite::SetScale(float x, float y)
	{
		this->scale = Vector(x, y);
		this->width = this->image->GetWidth()*x;
		this->height = this->image->GetHeight()*y;
	}
	void Sprite::SetScale(Vector vector)
	{
		SetScale(vector.x, vector.y);
	}
	void Sprite::SetWidth(float width)
	{
		this->scale.x = (float)width / this->image->GetWidth();
		this->width = width;
	}
	float Sprite::GetWidth()
	{
		//return this->image->GetWidth()*this->scale.x;
		return this->width;
	}
	void Sprite::SetHeight(float height)
	{
		this->scale.y = (float)height / this->image->GetHeight();
		this->height = height;
	}
	float Sprite::GetHeight()
	{
		//return this->image->GetHeight()*this->scale.y;
		return this->height;
	}
	
}
