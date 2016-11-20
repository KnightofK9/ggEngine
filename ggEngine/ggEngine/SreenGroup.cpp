#include "ScreenGroup.h"
#include "Sprite.h"
namespace ggEngine {
	ScreenGroup::ScreenGroup()
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
		Group::AddDrawObjectToList(drawObject);

	}

}
