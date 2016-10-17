#pragma once
#include <d3dx9core.h>
#include <tchar.h>
#include <string>
#include "GGObject.h" //All instance of class within engine must derived from GGObject
#include "DrawObject.h" //Text belong to group and must provide draw for group use for drawing on screen
#include "Font.h"
namespace ggEngine {
	//Text use Style to define text style. Re-Define any property of this style default value as you want
	enum Allign { Allign_Left, Allign_Middle, Allign_Right};
	struct Style {
		bool enableBackgroundColor = false;
		//A canvas fillstyle that will be used as the background for the whole Text object.Set to null to disable. Preserved for future using
		D3DCOLOR backgroundColor = D3DCOLOR_ARGB(0, 255, 255, 255);;
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
		Text(DrawManager *drawManager,Font *font, double x, double width, double height, double y, std::string text, Style style);
		//Release the font here
		~Text();
		//You MUST call the base GameObject::Destroy() in here. Destroy just set alive to false for collector take care
		void Destroy();
		void SetFont(Font *font) { this->font = font; }
		//Called by DrawManager, the translatedWorldMatrix is Camera Translated Matrix, you MUST multi matrix of the draw with Camera Matrix
		void Draw();
		void SetText(std::string text); 
		virtual void SetWidth(double width);
		virtual void SetHeight(double height);
		virtual double GetWidth();
		virtual double GetHeight(); 
		virtual void SetScale(double x, double y);
		virtual void SetScale(Vector vector);
		virtual void SetRotate(double rotate); 
		int GetOpacity() { return this->opacity; }
		void SetOpacity(int opacity) { this->opacity = opacity % 256; }
		void Transform(LPD3DXSPRITE spriteHandle);
	private:
		Font *font;
		Style style;
		std::string text;
		double orgWidth;
		double orgHeight;
		int opacity = 255;
	};
}

