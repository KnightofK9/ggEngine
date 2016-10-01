#include "Text.h"

Text::Text(LPDIRECT3DDEVICE9 device, int fontSize, char * fontFamily,
	int fontWeight, bool isItalic)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height = fontSize;
	fontDesc.Width = fontSize;
	fontDesc.Weight = fontWeight;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = isItalic;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy_s(fontDesc.FaceName, fontFamily);

	D3DXCreateFontIndirect(device, &fontDesc, &font);
}

Text::~Text()
{
	if (font != NULL)
	{
		font->Release();
		font = NULL;
	}
}

void Text::Draw(LPTSTR lpString, int posX, int posY, D3DCOLOR color)
{
		RECT R = { posX, posY, 0, 0 };
		font->DrawTextA(0, lpString, -1, &R, DT_NOCLIP, color);
}

