#include "ItemManager.h"
#include "CVGame.h"
#include "CVPreload.h"
#include "TextureConstant.h"
ItemManager::ItemManager(CVGame *cvGame):CVAdd(nullptr,cvGame)
{
	this->cvGame = cvGame;
	this->cvPreload = cvGame->cvPreload;
}
ItemManager::~ItemManager(){

}

void ItemManager::PreloadAllItem(){

	this->cvPreload->Texture(TextureConstant::HEART_MINI_TEXTURE, TextureConstant::HEART_MINI_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::HEART_LARGER_TEXTURE, TextureConstant::HEART_LARGER_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::AXE_TEXTURE, TextureConstant::AXE_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::BOOMERANG_TEXTURE, TextureConstant::BOONERANG_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::CANDLE_TEXTURE, TextureConstant::CANDLE_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::CROWN_TEXTURE, TextureConstant::CROWN_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::DAGGER_TEXTURE, TextureConstant::DAGGER_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::CROSS_TEXTURE, TextureConstant::CROSS_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::HOLY_WATER_TEXTURE, TextureConstant::HOLY_WATER_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::WHIP_UPGRADE_TEXTURE, TextureConstant::WHIP_UPGRADE_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::INVIN_POTION_TEXTURE, TextureConstant::INVIN_POTION_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_100_TEXTURE, TextureConstant::MONEY_BAG_100_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_700_TEXTURE, TextureConstant::MONEY_BAG_700_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_1000_TEXTURE, TextureConstant::MONEY_BAG_1000_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_400_TEXTURE, TextureConstant::MONEY_BAG_400_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::POT_ROAST_TEXTURE, TextureConstant::POT_ROAST_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::STOPWATCH_TEXTURE, TextureConstant::STOPWATCH_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::STUFF_TEXTURE, TextureConstant::STUFF_TEXTURE_PATH);
}

Heart * ItemManager::AddHeart(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::HEART_MINI_TEXTURE);
	Heart * heart = new Heart(this->cvGame, inf);
	heart->SetPosition(x, y);
	heart->Active();
	heart->CheckCollisionToSimon(this->cvGame->simon);
	group->AddDrawObjectToList(heart);
	return heart;
}
