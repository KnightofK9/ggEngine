#pragma once
#include <d3dx9core.h>
#include <tchar.h>
#include <string>

class Text
{
protected:
	LPD3DXFONT font;
	LPDIRECT3DDEVICE9 device;

public:
	Text(LPDIRECT3DDEVICE9 device, int fontSize, char * fontfamily = "Segoe UI",
		int fontWeight = 0, bool isItalic = false);
	~Text();

	void Draw(LPTSTR lpString, int posX, int posY, D3DCOLOR color);
};

