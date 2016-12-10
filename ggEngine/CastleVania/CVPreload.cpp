#include "CVPreload.h"
#include "CVGame.h"
CVPreload::CVPreload(CVGame * game) : ManagerBase(game)
{
	
}

CVPreload::~CVPreload()
{
}

void CVPreload::CharSimon()
{
	this->preload->Texture(TextureConstant::SIMON_TEXTURE, TextureConstant::SIMON_TEXTURE_PATH);
}

void CVPreload::UIInfoPanel()
{
	this->preload->Texture(TextureConstant::EMPTY_HEALTH_TEXTURE, TextureConstant::EMPTY_HEALTH_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::FULL_HEALTH_PLAYER_TEXTURE, TextureConstant::FULL_HEALTH_PLAYER_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::LIFE_TEXTURE, TextureConstant::LIFE_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::FULL_HEALTH_ENEMY_TEXTURE, TextureConstant::FULL_HEALTH_ENEMY_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ITEM_BOX_TEXTURE, TextureConstant::ITEM_BOX_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::NONE_TEXTURE, TextureConstant::NONE_TEXTURE_PATH);

	//this->Texture("Holy_water", "Resource/Resources/Holy_water.png");
}

void CVPreload::FontGame()
{
	this->preload->Font(TextureConstant::GAME_FONT_TEXTURE, TextureConstant::GAME_FONT_NAME, TextureConstant::GAME_FONT_TEXTURE_PATH, 20);
}
