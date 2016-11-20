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
ggEngine::Text::Text(DrawManager *drawManager,Font *font, double x, double y, double width, double height, std::string text, Style style):GameObject(drawManager)
{
	SetAnchor(0, 0);
	SetPosition(x, y);
	this->orgWidth = width;
	this->orgHeight = height;
	this->width = width;
	this->height = height;
	this->text = text;
	this->style = style;
	this->font = font;
	this->drawStyle = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
}

ggEngine::Text::~Text()
{
	
}

void ggEngine::Text::Destroy()
{
	GameObject::Destroy();
}

void ggEngine::Text::Draw()
{
	if (!visible) return;
	this->Transform(spriteHandle);
	//double width = GetWidth();
	//double height = GetHeight();
	RECT worldRect{ position.x - width*anchor.x, position.y - height*anchor.y, position.x + width*(1- anchor.x), position.y + height*(1 - anchor.y) };
	/*if (worldRect.left < 0)
		worldRect.left = 0;
	if (worldRect.top < 0)
		worldRect.top = 0;
	if (worldRect.right > GAME_WIDTH)
		worldRect.right = GAME_WIDTH;
	if (worldRect.bottom > GAME_HEIGHT)
		worldRect.bottom = GAME_HEIGHT;*/

	RECT rect{ 0 , 0 , width, height };
	if (spriteHandle->Begin(this->drawStyle) == D3D_OK)
	{
		
		style.backgroundColor = (style.backgroundColor & 0x00FFFFFF) | (opacity << 24);
		style.fontColor = (style.fontColor & 0x00FFFFFF) | (opacity << 24);
		if (style.enableBackgroundColor) this->drawManager->DrawRectangle(worldRect.left, worldRect.top, worldRect.right, worldRect.bottom, style.backgroundColor);
		font->GetDxFont()->DrawTextA(spriteHandle, text.c_str(), -1, &rect,DT_LEFT| DT_NOCLIP , style.fontColor);
		spriteHandle->End();
	}
}

void ggEngine::Text::SetText(std::string text)
{
	this->text = text;
}

void ggEngine::Text::SetWidth(double width)
{
	this->scale.x = (double)width / this->orgWidth;
	this->width = width;
}

void ggEngine::Text::SetHeight(double height)
{
	this->scale.y = (double)height / this->orgHeight;
	this->height = height;
}

double ggEngine::Text::GetWidth()
{
	return this->width;
}

double ggEngine::Text::GetHeight()
{
	return this->height;
}

void ggEngine::Text::SetScale(double x, double y)
{
	this->scale = Vector(x, y);
	this->width = this->orgWidth*x;
	this->height = this->orgHeight*y;
}

void ggEngine::Text::SetScale(Vector vector)
{
	Text::SetScale(vector.x, vector.y); 
}

void ggEngine::Text::SetRotate(double rotate)
{
	g_debug.Warning("Text can not be rotated in this version.");
}

void ggEngine::Text::Transform(LPD3DXSPRITE spriteHandle)
{
	//Scale from 0 0
	Matrix mat;
	mat = Matrix::CreateScaleMatrix(this->worldScale.x, this->worldScale.y);
	//Move to position
	mat *= Matrix::CreateTranslateMatrix(worldPosition.x - GetWidth()*scale.x / 2, worldPosition.y - GetHeight()*scale.y / 2);
	//Move anchor to position
	mat *= Matrix::CreateTranslateMatrix(GetWidth()*(0.5 - anchor.x), GetHeight()*(0.5 - anchor.y));
	//Rotate around anchor
	mat *= Matrix::CreateRotateMatrix(this->rotate);
	//Tranform to screen view
	//mat *= translatedWorldMatrix;

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

