#include "Font.h"
#include "DrawManager.h"
#include "Debug.h"
ggEngine::Font::Font(DrawManager * drawManager, std::string fontName, int fontSize, bool isItalic, int fontWeight)
{
	this->fontSize = fontSize;
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

void ggEngine::Font::Draw(double worldX, double worldY,std::string text, D3DCOLOR fontColor)
{
	RECT rect = { worldX,worldY,worldX,worldY };
	font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, fontColor);
}



//bool ggEngine::Font::AddFontToResource(std::string filePath)
//{
//	if (AddFontResourceEx(reinterpret_cast<LPCTSTR>(&filePath), FR_PRIVATE, NULL))
//		return false;
//	return true;
//}
//
//bool ggEngine::Font::RemoveFontFromResource(std::string fontName)
//{
//	if (!RemoveFontResourceEx(reinterpret_cast<LPCTSTR>(&fontName), FR_PRIVATE, NULL))
//		return false;
//	return true;
//}

 ggEngine::Font::Font(DrawManager *drawManager, std::string fontName, std::string fontPath, int fontSize, bool isItalic, int fontWeight)
{
	 this->fontSize = fontSize;
	 if (AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL) == 0)
	 {
		 g_debug.Error("Error: Cannot load font from file");
		 font = NULL;
		 return;
	 }
	 HRESULT hr = D3DXCreateFont(drawManager->GetDevice(),
		 fontSize,              //Font height
		 0,						//Font width
		 fontWeight,		    //Font Weight
		 1,		                //MipLevels
		 isItalic,		        //Italic
		 DEFAULT_CHARSET,		//CharSet
		 OUT_DEFAULT_PRECIS,	//OutputPrecision
		 ANTIALIASED_QUALITY,	//Quality
		 DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
		 fontName.c_str(),          //pFacename,
		 &font);         //ppFont
	 if (hr != S_OK) {
		 font = NULL;
	 }
}
