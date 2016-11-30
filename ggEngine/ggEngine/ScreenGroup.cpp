#include "ScreenGroup.h"
#include "Sprite.h"
#include "Text.h"
#include "Game.h"
namespace ggEngine {
	ScreenGroup::ScreenGroup(Game *game) : Group(game)
	{

	}

	ScreenGroup::~ScreenGroup()
	{
	}

	void ScreenGroup::AddDrawObjectToList(GameObject * drawObject)
	{
		Sprite *sprite = dynamic_cast<Sprite*>(drawObject);
		if (sprite != nullptr) {
			sprite->style = D3DXSPRITE_ALPHABLEND;
		}
		else {
			Text *text = dynamic_cast<Text*>(drawObject);
			if (text != nullptr) {
				text->drawStyle = D3DXSPRITE_ALPHABLEND;
			}
		}


		Group* parentGroup = (drawObject->GetParentObject());
		if (parentGroup != nullptr) parentGroup->GetDrawList()->remove(drawObject);
		drawObject->SetParentObject(this);
		drawList.push_back(drawObject);

	}

}
