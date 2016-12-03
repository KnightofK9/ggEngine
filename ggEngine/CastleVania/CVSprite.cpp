#include "CVSprite.h"
#include "CVAdd.h"


CVSprite::CVSprite(Game *game, SpriteInfo * image) : Sprite(game,image)
{
}

CVSprite::~CVSprite()
{
	//g_debug.Log("Deleting CVSprite");

}