#pragma once
#include <d3dx9core.h>
#include <tchar.h>
#include <string>
#include "GGObject.h" //All instance of class within engine must derived from GGObject
#include "DrawObject.h" //Text belong to group and must provide draw for group use for drawing on screen
namespace ggEngine {
	//Text use Style to define text style. Re-Define any property of this style default value as you want
	enum Allign { Allign_Left, Allign_Middle, Allign_Right};
	struct Style {
		//The font of text
		std::string font = "Arial"; 
		//The style of the font (eg. 'italic'). Preserved for future using
		std::string fontStyle = ""; 
		//The variant of the font (eg. 'small-caps'). Preserved for future using
		std::string fontVariant = "";
		//The weight of the font (eg. 'bold'). Preserved for future using
		std::string fontWeight = "";
		//The size of the font (eg. 32 , measure in px).
		int fontSize = 14;
		//A canvas fillstyle that will be used as the background for the whole Text object.Set to null to disable. Preserved for future using
		D3DCOLOR backgroundColor = D3DCOLOR_ARGB(255, 255, 255, 255);;
		//A canvas fillstyle that will be used on the text eg 'red', '#00FF00'. Preserved for future using
		std::string fill = "";
		//Horizontal alignment of each line in multiline text.Can be : 'left', 'center' or 'right'.Does not affect single lines of text. Preserved for future using
		std::string align = "left";
		//A canvas stroke style that will be used on the text stroke eg 'blue', '#FCFF00'. Preserved for future using
		D3DCOLOR strokeColor = DEFAULT_COLOR;
		//A number that represents the thickness of the stroke. Default is 0 (no stroke). Preserved for future using
		int strokeThickness = 0;
		D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 0, 0, 0);
		Allign horizontalAllign = Allign_Left;
		Allign verticalAllign = Allign_Left;
	};
	//All instance of class inside engine must have namespace ggEngine
	//Important, DrawObject derived from GameObject, GameObject already have position, scale, width, height. Just use position for this time
	//Text is add via class Add. There should be a preload for font too, but forget it for now. Use default system font
	class Text :public DrawObject {
	public:
		//Modify the constructor as you want, but must have those properties
		Text(LPDIRECT3DDEVICE9 device, float x, float width, float height, float y, std::string text, Style style);
		//Release the font here
		~Text();
		//You MUST call the base GameObject::Destroy() in here. Destroy just set alive to false for collector take care
		void Destroy();
		//Called by DrawManager, the translatedWorldMatrix is Camera Translated Matrix, you MUST multi matrix of the draw with Camera Matrix
		void Draw(Matrix translatedWorldMatrix, LPD3DXSPRITE spriteHandle);
		void SetText(std::string text); 
		virtual void SetWidth(float width);
		virtual void SetHeight(float height);
		virtual float GetWidth();
		virtual float GetHeight(); 
		virtual void SetScale(float x, float y);
		virtual void SetScale(Vector vector);
	private:
		LPD3DXFONT font;
		Style style;
		std::string text;
		float orgWidth;
		float orgHeight;
	};
}

