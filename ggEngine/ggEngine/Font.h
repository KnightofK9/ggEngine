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
		~Font();
		LPD3DXFONT GetDxFont() { return this->font; }
		void Draw(float worldX, float worldY, std::string text, D3DCOLOR fontColor = DEFAULT_COLOR);
		void Destroy();
	private:
		LPD3DXFONT font;
	};
}