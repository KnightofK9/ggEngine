#include "Sprite.h"
#include "Body.h"
namespace ggEngine {
	Sprite::Sprite(DrawManager *drawManager, std::string filename, D3DCOLOR transcolor) : DrawObject(drawManager)
	{
		this->type = SpriteType_Texture;
		this->image = new Texture(drawManager->GetDevice(), filename, transcolor);
		this->width = this->orgWidth = image->GetWidth();
		this->height = this->orgHeight = image->GetHeight();
		if (image->GetTexture() == NULL) {
			SetImage(new Texture(drawManager->GetDevice(), "default.bmp", transcolor));
		}
		/*HRESULT result = D3DXCreateSprite(device, &this->spriteHandle);
		if (result != D3D_OK)
		{
			this->spriteHandle = NULL;
			throw ERROR_CODE_FAIL_INIT_SPRITE_HANDLER;
		}*/
		this->anchor = Vector(0.5, 0.5);
		this->body = NULL;
	}
	Sprite::Sprite(DrawManager * drawManager, Texture * atlas, RECT atlasRect) : DrawObject(drawManager)
	{
		this->type = SpriteType_Atlas;
		this->image = atlas;
		this->atlasRect = atlasRect;
		this->width = this->orgWidth = atlasRect.right - atlasRect.left;
		this->height = this->orgHeight = atlasRect.bottom - atlasRect.top;
	}
	Sprite::Sprite(DrawManager *drawManager, Texture * image) : DrawObject(drawManager)
	{
		this->type = SpriteType_Texture;
		SetImage(image);
		this->anchor = Vector(0.5, 0.5);
		this->body = NULL;
	}

	Sprite::Sprite(DrawManager* drawManager) : DrawObject(drawManager)
	{
	}

	Sprite::~Sprite()
	{
	}
	void Sprite::Draw(Matrix translatedWorldMatrix)
	{
		Transform(translatedWorldMatrix, spriteHandle);
		RECT srcRect;
		if (type == SpriteType_Texture)
		{
			srcRect = { 0, 0, (long)this->orgWidth, (long)this->orgHeight };
		}
		else {
			srcRect = atlasRect;
		}
		if (!visible) return;
		if (spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			spriteHandle->Draw(this->GetImage()->GetTexture(), &srcRect, NULL, NULL, D3DCOLOR_RGBA(255, 255, 255, opacity));
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
		this->type = SpriteType_Texture;
		this->image = image;
		this->width = this->orgWidth = image->GetWidth();
		this->height = this->orgHeight = image->GetHeight();
	}
	void Sprite::SetScale(float x, float y)
	{
		this->scale = Vector(x, y);
		this->width = this->orgWidth*x;
		this->height = this->orgHeight*y;
	}
	void Sprite::SetScale(Vector vector)
	{
		SetScale(vector.x, vector.y);
	}
	void Sprite::SetWidth(float width)
	{
		this->scale.x = (float)width / this->orgWidth;
		this->width = width;
	}
	float Sprite::GetWidth()
	{
		//return this->image->GetWidth()*this->scale.x;
		return this->width;
	}
	void Sprite::SetHeight(float height)
	{
		this->scale.y = (float)height / this->orgHeight;
		this->height = height;
	}
	float Sprite::GetHeight()
	{
		//return this->image->GetHeight()*this->scale.y;
		return this->height;
	}
	
}
