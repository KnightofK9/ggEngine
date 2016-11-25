#include "ItemManager.h"
#include "CVGame.h"
#include "CVPreload.h"
#include "CVAdd.h"
#include "TextureConstant.h"
ItemManager::ItemManager(CVGame *cvGame){
	this->cvGame = cvGame;
	this->cvAdd = new CVAdd(nullptr, cvGame);
	this->cvPreload = new CVPreload(cvGame->cache);
}
ItemManager::~ItemManager(){

}

void ItemManager::PreloadAllItem(){
	//this->cvPreload->Texture(TextureConstant::BAT_ANIM_TEXTURE, TextureConstant::BAT_ANIM_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::INTRO_BG_TEXTURE, TextureConstant::INTRO_BG_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::HELICOPTER_TEXTURE, TextureConstant::HELICOPTER_TEXTURE_PATH);

	this->cvPreload->Texture(TextureConstant::HEART_MINI_TEXTURE, TextureConstant::HEART_MINI_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::HEART_LARGER_TEXTURE, TextureConstant::HEART_LARGER_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::AXE_TEXTURE, TextureConstant::AXE_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::BOOMERANG_TEXTURE, TextureConstant::BOONERANG_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::CANDLE_TEXTURE, TextureConstant::CANDLE_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::CROWN_TEXTURE, TextureConstant::CROWN_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::DAGGER_TEXTURE, TextureConstant::DAGGER_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::DEAD_TEXTURE, TextureConstant::DEAD_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::BOOMERANG_WEAPON_TEXTURE, TextureConstant::BOOMERANG_WEAPON_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::AXE_WEAPON_TEXTURE, TextureConstant::AXE_WEAPON_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::MAIN_WEAPON_TEXTURE, TextureConstant::MAIN_WEAPON_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::CROSS_TEXTURE, TextureConstant::CROSS_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::HOLY_WATER_TEXTURE, TextureConstant::HOLY_WATER_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::HOLY_WATER_WEAPON_TEXTURE, TextureConstant::HOLY_WATER_WEAPON_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::HIT_TEXTURE, TextureConstant::HIT_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::WHIP_UPGRADE_TEXTURE, TextureConstant::WHIP_UPGRADE_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::DOUBLESHOT_TEXTURE, TextureConstant::DOUBLESHOT_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::INVIN_POTION_TEXTURE, TextureConstant::INVIN_POTION_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_100_TEXTURE, TextureConstant::MONEY_BAG_100_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_700_TEXTURE, TextureConstant::MONEY_BAG_700_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_1000_TEXTURE, TextureConstant::MONEY_BAG_1000_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::MONEY_BAG_400_TEXTURE, TextureConstant::MONEY_BAG_400_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::POT_ROAST_TEXTURE, TextureConstant::POT_ROAST_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::SPLASH_EFFECT_TEXTURE, TextureConstant::SPLASH_EFFECT_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::STOPWATCH_TEXTURE, TextureConstant::STOPWATCH_TEXTURE_PATH);
	this->cvPreload->Texture(TextureConstant::STUFF_TEXTURE, TextureConstant::STUFF_TEXTURE_PATH);
	//this->cvPreload->Texture(TextureConstant::TRIPLE_SHOT_TEXTURE, TextureConstant::TRIPLE_SHOT_TEXTURE_PATH);
}
void ItemManager::AddHealthPotion(double x, double y, Group *group){
	this->heartMini = cvAdd->Sprite(50, 650, TextureConstant::HEART_MINI_TEXTURE, group);
	this->heartMini->SetAnchor(0.5, 0.5);
	this->heartMini->SetScale(3, 3);
	this->heartMini->tag = ObjectType_Static;
	this->cvGame->physics->EnablePhysics(this->heartMini);
	this->heartMini->body->CreateRectangleRigidBody(100, 100);
	this->heartMini->body->rigidBody->SetAnchor(0.5, 0.5);
	this->heartMini->body->allowGravity = true;
}