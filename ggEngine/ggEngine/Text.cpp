#include "Text.h"
#include "Debug.h"
//Text::Text(LPDIRECT3DDEVICE9 device, int fontSize, char * fontFamily,
//	int fontWeight, bool isItalic)
//{
//	D3DXFONT_DESC fontDesc;
//	fontDesc.Height = fontSize;
//	fontDesc.Width = fontSize;
//	fontDesc.Weight = fontWeight;
//	fontDesc.MipLevels = 1;
//	fontDesc.Italic = isItalic;
//	fontDesc.Quality = DEFAULT_QUALITY;
//	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
//	_tcscpy_s(fontDesc.FaceName, fontFamily);
//
//	D3DXCreateFontIndirect(device, &fontDesc, &font);
//}
//
//Text::~Text()
//{
//	if (font != NULL)
//	{
//		font->Release();
//		font = NULL;
//	}
//}
//
//void Text::Draw(LPTSTR lpString, int posX, int posY, D3DCOLOR color)
//{
//		RECT R = { posX, posY, 0, 0 };
//		font->DrawTextA(0, lpString, -1, &R, DT_NOCLIP, color);
//}

ggEngine::Text::Text(DrawManager *drawManager, float x, float y, float width, float height, std::string text, Style style):DrawObject(drawManager)
{
	bool isItalic = style.fontStyle.find("italic") != std::string::npos;
	SetPosition(x, y);
	this->orgWidth = width;
	this->orgHeight = height;
	this->width = width;
	this->height = height;
	this->text = text;
	this->style = style;
	HRESULT hr = D3DXCreateFont(drawManager->GetDevice(),     //D3D Device
		style.fontSize,               //Font height
		0,                //Font width
		FW_NORMAL,        //Font Weight
		1,                //MipLevels
		isItalic,            //Italic
		DEFAULT_CHARSET,  //CharSet
		OUT_DEFAULT_PRECIS, //OutputPrecision
		ANTIALIASED_QUALITY, //Quality
		DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
		style.font.c_str(),          //pFacename,
		&font);         //ppFont
}

ggEngine::Text::~Text()
{
	if (font != NULL) {
		font->Release();
		font = NULL;
	}
}

void ggEngine::Text::Destroy()
{
	GameObject::Destroy();
}

void ggEngine::Text::Draw(Matrix translatedWorldMatrix)
{
	if (!visible) return;
	this->Transform(translatedWorldMatrix, spriteHandle);
	//float width = GetWidth();
	//float height = GetHeight();
	RECT worldRect{ position.x - width*anchor.x, position.y - height*anchor.y, position.x + width*(1- anchor.x), position.y + height*(1 - anchor.y) };
	if (worldRect.left < 0)
		worldRect.left = 0;
	if (worldRect.top < 0)
		worldRect.top = 0;
	if (worldRect.right > WINDOW_WIDTH)
		worldRect.right = WINDOW_WIDTH;
	if (worldRect.bottom > WINDOW_HEIGHT)
		worldRect.bottom = WINDOW_HEIGHT;

	RECT rect{ 0 , 0 , width, height };
	if (spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
	{
		drawManager->DrawRectangle(worldRect.left, worldRect.top, worldRect.right, worldRect.bottom, style.backgroundColor);
		font->DrawTextA(spriteHandle, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_NOCLIP, style.fontColor);
		spriteHandle->End();
	}
}

void ggEngine::Text::SetText(std::string text)
{
	this->text = text;
}

void ggEngine::Text::SetWidth(float width)
{
	this->scale.x = (float)width / this->orgWidth;
	this->width = width;
}

void ggEngine::Text::SetHeight(float height)
{
	this->scale.y = (float)height / this->orgHeight;
	this->height = height;
}

float ggEngine::Text::GetWidth()
{
	return this->width;
}

float ggEngine::Text::GetHeight()
{
	return this->height;
}

void ggEngine::Text::SetScale(float x, float y)
{
	this->scale = Vector(x, y);
	this->width = this->orgWidth*x;
	this->height = this->orgHeight*y;
}

void ggEngine::Text::SetScale(Vector vector)
{
	Text::SetScale(vector.x, vector.y); 
}

void ggEngine::Text::SetRotate(float rotate)
{
	Debug::Warning("Text can not be rotated in this version.");
}

void ggEngine::Text::Transform(Matrix translatedWorldMatrix, LPD3DXSPRITE spriteHandle)
{
	//Scale from 0 0
	Matrix mat;
	mat = Matrix::CreateScaleMatrix(this->scale.x, this->scale.y);
	//Move to anchor
	mat *= Matrix::CreateTranslateMatrix((1-scale.x)*width*anchor.x, (1-scale.y)*height*anchor.y);
	//Rotate around anchor
	mat *= Matrix::CreateRotateMatrix(this->rotate);
	//Translate to exact anchor and position
	mat *= Matrix::CreateTranslateMatrix(this->position.x - this->GetWidth()/2, this->position.y - this->GetHeight()/2);
	//Tranform to screen view
	mat *= translatedWorldMatrix;

	//Vector scaleTransform(this->scale.x, this->scale.y);
	//Vector rotateCenter((this->width) / 2, (this->height) / 2);
	////Vector scaleCenter((this->width) / 2, (this->height) / 2);
	//Vector trans(this->position.x - this->width*(this->anchor.x), this->position.y - this->height*(this->anchor.y));
	//D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &rotateCenter, this->rotate, &trans);
	//mat *= (Matrix::CreateScaleMatrix(1, -1)*Matrix::CreateTranslateMatrix(0, this->height));

	//if (this->body != NULL)
	//	this->body->rigidBody->Transform(mat);
	spriteHandle->SetTransform(&mat);
}
