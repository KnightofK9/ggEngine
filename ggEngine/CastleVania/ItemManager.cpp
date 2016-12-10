#include "ItemManager.h"
#include "CVGame.h"
#include "CVPreload.h"
#include "TextureConstant.h"

ItemManager::ItemManager(CVGame * cvGame)
{
	this->cvGame = cvGame;
	this->preload = cvGame->preload;
	this->add = cvGame->add;
	this->cvPreload = cvGame->cvPreload;
	this->cvAdd = cvGame->cvAdd;
	this->cache = cvGame->cache;
}
ItemManager::~ItemManager(){

}

void ItemManager::PreloadAllItem(){

	this->preload->Texture(TextureConstant::HEART_MINI_TEXTURE, TextureConstant::HEART_MINI_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::HEART_LARGER_TEXTURE, TextureConstant::HEART_LARGER_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::AXE_TEXTURE, TextureConstant::AXE_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::BOOMERANG_TEXTURE, TextureConstant::BOONERANG_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::CANDLE_TEXTURE, TextureConstant::CANDLE_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::CROWN_TEXTURE, TextureConstant::CROWN_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::DAGGER_TEXTURE, TextureConstant::DAGGER_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::CROSS_TEXTURE, TextureConstant::CROSS_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::HOLY_WATER_TEXTURE, TextureConstant::HOLY_WATER_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::WHIP_UPGRADE_TEXTURE, TextureConstant::WHIP_UPGRADE_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::INVIN_POTION_TEXTURE, TextureConstant::INVIN_POTION_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::MONEY_BAG_100_TEXTURE, TextureConstant::MONEY_BAG_100_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::MONEY_BAG_700_TEXTURE, TextureConstant::MONEY_BAG_700_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::MONEY_BAG_1000_TEXTURE, TextureConstant::MONEY_BAG_1000_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::MONEY_BAG_400_TEXTURE, TextureConstant::MONEY_BAG_400_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::POT_ROAST_TEXTURE, TextureConstant::POT_ROAST_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::STOPWATCH_TEXTURE, TextureConstant::STOPWATCH_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::STUFF_TEXTURE, TextureConstant::STUFF_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::DOUBLESHOT_TEXTURE, TextureConstant::DOUBLESHOT_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::TRIPLE_SHOT_TEXTURE, TextureConstant::TRIPLE_SHOT_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::MAIN_WEAPON_TEXTURE, TextureConstant::MAIN_WEAPON_TEXTURE_PATH);
}

Heart * ItemManager::AddHeart(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::HEART_MINI_TEXTURE);
	Heart * heart = new Heart(this->cvGame, inf);
	heart->SetPosition(x, y);
	heart->Active();
	//heart->CheckCollisionToSimon(this->cvGame->simon);
	if (group != nullptr) {
		heart->SetParentObject(group);
		group->AddDrawObjectToList(heart);
	}
	return heart;
}

AxeItem * ItemManager::AddAxe(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::AXE_TEXTURE);
	AxeItem *axe = new AxeItem(this->cvGame, inf);
	axe->SetPosition(x, y);
	axe->Active();
	//axe->CheckCollisionToSimon(this->cvGame->simon);
	if (group != nullptr) {
		axe->SetParentObject(group);
		group->AddDrawObjectToList(axe);
	}
	return axe;
}

MoneyBag100 * ItemManager::AddMoneyBag100(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::MONEY_BAG_100_TEXTURE);
	MoneyBag100 *moneyBag = new MoneyBag100(this->cvGame, inf);
	moneyBag->SetPosition(x, y);
	moneyBag->Active();
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	if (group != nullptr) {
		moneyBag->SetParentObject(group);
		group->AddDrawObjectToList(moneyBag);
	}
	return moneyBag;
}

MoneyBag400 * ItemManager::AddMoneyBag400(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::MONEY_BAG_400_TEXTURE);
	MoneyBag400 *moneyBag = new MoneyBag400(this->cvGame, inf);
	moneyBag->SetPosition(x, y);
	moneyBag->Active();
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	if (group != nullptr) {
		moneyBag->SetParentObject(group);
		group->AddDrawObjectToList(moneyBag);
	}
	return moneyBag;
}

MoneyBag700 * ItemManager::AddMoneyBag700(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::MONEY_BAG_700_TEXTURE);
	MoneyBag700 *moneyBag = new MoneyBag700(this->cvGame, inf);
	moneyBag->SetPosition(x, y);
	moneyBag->Active();
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	if (group != nullptr) {
		moneyBag->SetParentObject(group);
		group->AddDrawObjectToList(moneyBag);
	}
	return moneyBag;
}

 MoneyBag1000* ItemManager::AddMoneyBag1000(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::MONEY_BAG_1000_TEXTURE);
	MoneyBag1000 *moneyBag = new MoneyBag1000(this->cvGame, inf, 14, 15, 0, 3, 100);
	moneyBag->CreateAnimation("moneyBag1000", 0, 2, true);
	moneyBag->SetPosition(x, y);
	moneyBag->PlayAnimation("moneyBag1000");
	moneyBag->Active();
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	if (group != nullptr) {
		moneyBag->SetParentObject(group);
		group->AddDrawObjectToList(moneyBag);
	}
	return moneyBag;
}

 HolyWaterItem* ItemManager::AddHolyWater(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::HOLY_WATER_TEXTURE);
	 HolyWaterItem *holyWater = new HolyWaterItem(this->cvGame, inf);
	 holyWater->SetPosition(x, y);
	 holyWater->Active();
	 //holyWater->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 holyWater->SetParentObject(group);
		 group->AddDrawObjectToList(holyWater);
	 }
	 return holyWater;
 }

 DaggerItem* ItemManager::AddDagger(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::DAGGER_TEXTURE);
	 DaggerItem *dragger = new DaggerItem(this->cvGame, inf);
	 dragger->SetPosition(x, y);
	 dragger->Active();
	 //dragger->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 dragger->SetParentObject(group);
		 group->AddDrawObjectToList(dragger);
	 }
	 return dragger;
 }

 Cross* ItemManager::AddCross(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::CROSS_TEXTURE);
	 Cross *cross = new Cross(this->cvGame, inf);
	 cross->SetPosition(x, y);
	 cross->Active();
	 //cross->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 cross->SetParentObject(group);
		 group->AddDrawObjectToList(cross);
	 }
	 return cross;
 }

 Crown* ItemManager::AddCrown(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::MONEY_BAG_100_TEXTURE);
	 Crown *crown = new Crown(this->cvGame, inf);
	 crown->SetPosition(x, y);
	 crown->Active();
	 //crown->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 crown->SetParentObject(group);
		 group->AddDrawObjectToList(crown);
	 }
	 return crown;
 }

 StopWatch* ItemManager::AddStopWatch(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::STOPWATCH_TEXTURE);
	 StopWatch *stopWatch = new StopWatch(this->cvGame, inf);
	 stopWatch->SetPosition(x, y);
	 stopWatch->Active();
	 //stopWatch->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 stopWatch->SetParentObject(group);
		 group->AddDrawObjectToList(stopWatch);
	 }
	 return stopWatch;
 }

 PotRoast* ItemManager::AddPotRoast(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::POT_ROAST_TEXTURE);
	 PotRoast *potRoast = new PotRoast(this->cvGame, inf);
	 potRoast->SetPosition(x, y);
	 potRoast->Active();
	 //potRoast->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 potRoast->SetParentObject(group);
		 group->AddDrawObjectToList(potRoast);
	 }
	 return potRoast;
 }

 InvinPotion* ItemManager::AddInvinPotion(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::INVIN_POTION_TEXTURE);
	 InvinPotion *invinPotion = new InvinPotion(this->cvGame, inf);
	 invinPotion->SetPosition(x, y);
	 invinPotion->Active();
	 //invinPotion->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 invinPotion->SetParentObject(group);
		 group->AddDrawObjectToList(invinPotion);
	 }
	 return invinPotion;
 }

 HeartLarger* ItemManager::AddHeartLarger(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::MONEY_BAG_100_TEXTURE);
	 HeartLarger *heartLarger = new HeartLarger(this->cvGame, inf);
	 heartLarger->SetPosition(x, y);
	 heartLarger->Active();
	 //heartLarger->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 heartLarger->SetParentObject(group);
		 group->AddDrawObjectToList(heartLarger);
	 }
	 return heartLarger;
 }

 WhipUpgradeItem* ItemManager::AddWhipUpgrade(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::WHIP_UPGRADE_TEXTURE);
	 WhipUpgradeItem *whip = new WhipUpgradeItem(this->cvGame, inf);
	 whip->SetPosition(x, y);
	 whip->Active();
	 //whip->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 whip->SetParentObject(group);
		 group->AddDrawObjectToList(whip);
	 }
	 return whip;
 }

 Stuff* ItemManager::AddStuff(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::STUFF_TEXTURE);
	 Stuff *stuff = new Stuff(this->cvGame, inf, 16, 16, 0, 2, 150);
	 stuff->CreateAnimation("stuff", 0, 1, true);
	 stuff->SetPosition(x, y);
	 stuff->PlayAnimation("stuff");
	 stuff->Active();
	 //stuff->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 stuff->SetParentObject(group);
		 group->AddDrawObjectToList(stuff);
	 }
	 return stuff;
 }

 BoomerangItem* ItemManager::AddBoomerang(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::BOOMERANG_TEXTURE);
	 BoomerangItem *boomerang = new BoomerangItem(this->cvGame, inf);
	 boomerang->SetPosition(x, y);
	 boomerang->Active();
	 //boomerang->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 boomerang->SetParentObject(group);
		 group->AddDrawObjectToList(boomerang);
	 }
	 return boomerang;
 } 
 
 DoubleShot* ItemManager::AddDoubleShot(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::DOUBLESHOT_TEXTURE);
	 DoubleShot *doubleShot = new DoubleShot(this->cvGame, inf);
	 doubleShot->SetPosition(x, y);
	 doubleShot->Active();
	 //doubleShot->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 doubleShot->SetParentObject(group);
		 group->AddDrawObjectToList(doubleShot);
	 }
	 return doubleShot;
 } 
 
 TripleShot* ItemManager::AddTripleShot(double x, double y, ggEngine::Group * group)
 {
	 SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::TRIPLE_SHOT_TEXTURE);
	 TripleShot *tripleShot = new TripleShot(this->cvGame, inf);
	 tripleShot->SetPosition(x, y);
	 tripleShot->Active();
	 //tripleShot->CheckCollisionToSimon(this->cvGame->simon);
	 if (group != nullptr) {
		 tripleShot->SetParentObject(group);
		 group->AddDrawObjectToList(tripleShot);
	 }

	 return tripleShot;
 }
