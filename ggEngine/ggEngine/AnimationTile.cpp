#include "AnimationTile.h"
#include "TileMap.h"
#include "SingleTile.h"
#include "Game.h"
namespace ggEngine {
	AnimationTile::AnimationTile(Game *game, TileMap *tileMap):Sprite(game)
	{
		SetAnchor(0, 0);
		SetParentObject(tileMap);
		this->currentAnim = 0;
		this->size = 0;
	}
	AnimationTile::~AnimationTile()
	{
		for (auto it = this->tileAnimationList.begin(); it != this->tileAnimationList.end(); ++it)
		{
			delete (*it);
		}
		this->tileAnimationList.clear();
	}
	void AnimationTile::AddTileAnimation(SingleTile * singleTile)
	{
		//singleTile->SetParentObject(this);
		this->tileAnimationList.push_back(singleTile);
		this->size++;
	}
	void AnimationTile::Draw()
	{
		this->tileAnimationList[this->currentAnim]->Draw();
		this->currentAnim = (this->currentAnim + 1) / this->size;
	}
}

