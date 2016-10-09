#include "Font.h"
#include "DrawManager.h"
ggEngine::Font::Font(DrawManager * drawManager, std::string fontName, int fontSize, bool isItalic, int fontWeight)
{
	HRESULT hr = D3DXCreateFont(drawManager->GetDevice(),     //D3D Device
		fontSize,               //Font height
		0,                //Font width
		fontWeight,        //Font Weight
		1,                //MipLevels
		isItalic,            //Italic
		DEFAULT_CHARSET,  //CharSet
		OUT_DEFAULT_PRECIS, //OutputPrecision
		ANTIALIASED_QUALITY, //Quality
		DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
		fontName.c_str(),          //pFacename,
		&font);         //ppFont
	if(hr != S_OK){
		//TO DO new Debug here
		font = NULL;
	}
}

ggEngine::Font::~Font()
{
	if (font != NULL) font->Release();
	font = NULL;
}

void ggEngine::Font::Draw(float worldX, float worldY,std::string text, D3DCOLOR fontColor)
{
	RECT rect = { 0,0,worldX,worldY };
	font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, fontColor);
}

void ggEngine::Font::Destroy()
{
}
