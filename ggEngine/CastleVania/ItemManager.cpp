#include "ItemManager.h"
#include "CVGame.h"
#include "CVPreload.h"
#include "CVAdd.h"
ItemManager::ItemManager(CVGame *cvGame){
	this->cvGame = cvGame;
	this->cvAdd = new CVAdd(nullptr, cvGame);
	this->cvPreload = new CVPreload(cvGame->cache);
}
ItemManager::~ItemManager(){

}

void ItemManager::PreloadAllItem(){
	//TO DO preload all list of item here
}
void ItemManager::AddHealthPotion(double x, double y, Group *group){
	//TO DO example add health potion at position
}