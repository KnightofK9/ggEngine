#pragma once
#include <d3dx9core.h>
#include "GGObject.h"
#include <string>
#include "ConstantEnum.h"
namespace ggEngine {
	class DrawManager;
	class Font : public GGObject {
	public:
		Font(DrawManager *drawManager, std::string fontName, int fontSize, bool isItalic, int fontWeight = FW_NORMAL);
		Font(DrawManager *drawManager, std::string fontName, std::string fontPath, int fontSize, bool isItalic = false, int fontWeight = FW_NORMAL); //Load font from file
		~Font();
		LPD3DXFONT GetDxFont() { return this->font; }
		void Draw(double worldX, double worldY, std::string text, D3DCOLOR fontColor = DEFAULT_COLOR);
		void Destroy();

		//static bool AddFontToResource(std::string filePath);
		//static bool RemoveFontFromResource(std::string fontName);

	private:
		LPD3DXFONT font;
	};
}