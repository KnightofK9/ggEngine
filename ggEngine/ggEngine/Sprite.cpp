#include "Sprite.h"
#include "Body.h"
namespace ggEngine {
	Sprite::Sprite(LPDIRECT3DDEVICE9 device)
	{
		HRESULT result = D3DXCreateSprite(device, &this->spriteHandle);
		if (result != D3D_OK)
		{
			this->spriteHandle = NULL;
			throw ERROR_CODE_FAIL_INIT_SPRITE_HANDLER;
		}
		this->anchor = Vector(0.5, 0.5);
		this->body = NULL;
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
		this->anchor = Vector(0.5, 0.5);
		this->body = NULL;
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
		this->anchor = Vector(0.5, 0.5);
		this->body = NULL;
	}
	Sprite::~Sprite()
	{
		//TO DO remove sprite here
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
	void Sprite::Draw(Matrix translatedWorldMatrix)
	{
		Transform(translatedWorldMatrix);
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
		return this->image->GetWidth()*this->scale.x;
	}
	void Sprite::SetHeight(float height)
	{
		this->scale.y = (float)height / this->image->GetHeight();
		this->height = height;
	}
	float Sprite::GetHeight()
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
	void Sprite::Transform(Matrix translatedWorldMatrix)
	{
		//Scale from 0 0
		Matrix mat = Matrix::CreateScaleMatrix(this->scale.x, this->scale.y);
		//Move to anchor
		 mat *= Matrix::CreateTranslateMatrix(-this->GetWidth()*(this->anchor.x), -this->GetHeight()*(this->anchor.y));
		//Rotate around anchor
		mat *= Matrix::CreateRotateMatrix(this->rotate);
		//Translate to exact anchor and position
		mat *= Matrix::CreateTranslateMatrix(this->position.x , this->position.y );
		//Tranform to screen view
		mat *= translatedWorldMatrix;

		//Vector scaleTransform(this->scale.x, this->scale.y);
		//Vector rotateCenter((this->width) / 2, (this->height) / 2);
		////Vector scaleCenter((this->width) / 2, (this->height) / 2);
		//Vector trans(this->position.x - this->width*(this->anchor.x), this->position.y - this->height*(this->anchor.y));
		//D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &rotateCenter, this->rotate, &trans);
		//mat *= (Matrix::CreateScaleMatrix(1, -1)*Matrix::CreateTranslateMatrix(0, this->height));
		if(this->body!=NULL)
			this->body->rigidBody->Transform(mat);
		this->spriteHandle->SetTransform(&mat);
	}
}
