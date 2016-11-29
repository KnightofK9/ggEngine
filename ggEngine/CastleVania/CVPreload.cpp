#include "CVPreload.h"

CVPreload::CVPreload(Cache * cache):Preload(cache)
{
}

CVPreload::~CVPreload()
{
}

void CVPreload::CharSimon()
{
	this->Texture(TextureConstant::SIMON_TEXTURE, TextureConstant::SIMON_TEXTURE_PATH);
}

void CVPreload::UIInfoPanel()
{
	this->Texture(TextureConstant::EMPTY_HEALTH_TEXTURE, TextureConstant::EMPTY_HEALTH_TEXTURE_PATH);
	this->Texture(TextureConstant::FULL_HEALTH_PLAYER_TEXTURE, TextureConstant::FULL_HEALTH_PLAYER_TEXTURE_PATH);
	this->Texture(TextureConstant::LIFE_TEXTURE, TextureConstant::LIFE_TEXTURE_PATH);
	this->Texture(TextureConstant::FULL_HEALTH_ENEMY_TEXTURE, TextureConstant::FULL_HEALTH_ENEMY_TEXTURE_PATH);
	this->Texture(TextureConstant::ITEM_BOX_TEXTURE, TextureConstant::ITEM_BOX_TEXTURE_PATH);

	this->Texture("Holy_water", "Resource/Resources/Holy_water.png");
}

void CVPreload::FontGame()
{
	this->Font(TextureConstant::GAME_FONT_TEXTURE, TextureConstant::GAME_FONT_NAME, TextureConstant::GAME_FONT_TEXTURE_PATH, 20);
}