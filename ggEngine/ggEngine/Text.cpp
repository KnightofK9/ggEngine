#include "Text.h"

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

ggEngine::Text::Text(LPDIRECT3DDEVICE9 device, float x, float y, float width, float height, std::string text, Style style)
{
	bool isItalic = style.fontStyle.find("italic") != std::string::npos;
	SetPosition(x, y);
	this->orgWidth = width;
	this->orgHeight = height;
	this->width = width;
	this->height = height;
	this->text = text;
	this->style = style;
	HRESULT hr = D3DXCreateFont(device,     //D3D Device
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

void ggEngine::Text::Draw(Matrix translatedWorldMatrix, LPD3DXSPRITE spriteHandle)
{
	if (!visible) return;
	Transform(translatedWorldMatrix, spriteHandle);
	RECT rect{ 0, 0, position.x, position.y };
	//font->DrawTextA(nullptr, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, style.fontColor);
	if (spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
	{
		font->DrawTextA(spriteHandle, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, style.fontColor);
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
