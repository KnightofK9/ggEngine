#include "CVAdd.h"
#include "TextureConstant.h"
#include "TypeEnum.h"
#include "CharacterConstant.h"
#include "StateConstant.h"

CVAdd::CVAdd(CVGame *cvGame) : ManagerBase(cvGame)
{

}

CVAdd::~CVAdd()
{
}

Simon* CVAdd::CharSimon(double x, double y, int health, InfoPanel *infoPanel, GameOverScreen *goScreen, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::SIMON_TEXTURE);
	Simon *simon = new Simon(this->cvGame, inf,infoPanel, goScreen, 45, 40, 0,0, 130);
	simon->SetPosition(x, y);
	simon->SetOpacityAffectByParent(false);
	
	if (group != nullptr) {
		simon->SetParentObject(group);
		group->AddDrawObjectToList(simon);
	}

	//this->cvGame->camera->Follow(simon);

	return simon;
}

InfoPanel* CVAdd::UIInfoPanel(GameOverScreen *goScreen, ggEngine::Group *group)
{

	InfoPanel *infoPanel = new InfoPanel(this->cvGame);
	Style style;
	int fontSize = 22;
	int margin = 20;
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	
#pragma region  First line
	infoPanel->score		= this->add->Text(	margin, margin, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "SCORE—", style, infoPanel);
	infoPanel->scorePoint	= this->add->Text(	10 + fontSize*6,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50, 
											"000000",
											style,
											infoPanel);

	infoPanel->time			= this->add->Text(	GAME_WIDTH/2 - fontSize*4,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"TIME",
											style,
											infoPanel);

	infoPanel->timePoint	= this->add->Text(	infoPanel->time->GetX() + fontSize*5, 
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											ggEngine::Helper::IntToString(StateConstant::MAX_TIME_IN_LEVEL_1, 4),
											style,
											infoPanel);
	
	//infoPanel->timeInfo = this->add->LoopInfinity(1000, [infoPanel] {
	//	if (infoPanel->GetTime() <= 0)
	//		infoPanel->StopTime();
	//	else {
	//		infoPanel->SetTime(infoPanel->GetTime() - 1);
	//		infoPanel->timePoint->SetText(ggEngine::Helper::IntToString(infoPanel->GetTime(), 4));
	//	}
	//})->Start();
	//infoPanel->StartTime();


	infoPanel->stage		= this->add->Text(	GAME_WIDTH - fontSize*10, 
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"STAGE",
											style,
											infoPanel);

	infoPanel->stagePoint	= this->add->Text(	infoPanel->stage->GetX() + fontSize*6,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"01",
											style,
											infoPanel);
#pragma endregion

#pragma region  Second line
	infoPanel->player		= this->add->Text(	margin,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"PLAYER",
											style,
											infoPanel);

	infoPanel->playerHealthBar = this->UIPlayerHealthBar(margin + fontSize*7, margin + fontSize, infoPanel);
	infoPanel->playerHealthBar->SetScale(1.3, 1.3);

	infoPanel->heartIcon		= this->add->Sprite(	GAME_WIDTH / 2 + 110 + fontSize,
											margin + fontSize + 10,
											TextureConstant::LIFE_TEXTURE,
											infoPanel);
	infoPanel->heartIcon->SetAnchor(0.5, 0.5);
	infoPanel->heartIcon->SetScale(2.5, 2.5);
#pragma endregion

#pragma region  Third line
	infoPanel->enemy		= this->add->Text(	margin,
											margin + fontSize*2,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"ENEMY",
											style,
											infoPanel);
	infoPanel->enemyHealthBar = this->UIEnemyHealthBar(margin + fontSize*7, margin + fontSize * 2, infoPanel);
	infoPanel->enemyHealthBar->SetScale(1.3, 1.3);

#pragma endregion
	//P-H
	infoPanel->heart			= this->add->Text(	GAME_WIDTH / 2 + 100 + fontSize*2,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"-",
											style,
											infoPanel);

	infoPanel->heartPoint	= this->add->Text(	GAME_WIDTH/2 + 100 + fontSize*3,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"05",
											style,
											infoPanel);
	infoPanel->p			= this->add->Text(	GAME_WIDTH / 2 + 100 + fontSize,
											margin + fontSize * 2,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"P-",
											style,
											infoPanel);

	infoPanel->pPoint		= this->add->Text(	GAME_WIDTH/2 + 100 + fontSize*3,
											margin + fontSize * 2,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"03",
											style,
											infoPanel);

	infoPanel->itemBox		= this->add->Sprite(419, 75, "ItemBox", infoPanel);
	infoPanel->itemBox->SetAnchor(0.5, 0.5);
	infoPanel->itemBox->SetScale(3, 3);

	infoPanel->item = this->add->Sprite(408, 65, TextureConstant::NONE_TEXTURE, infoPanel);
	infoPanel->item->SetAnchor(0.5, 0.5);
	infoPanel->item->SetScale(2.5, 2.5);

	infoPanel->itemShot = this->add->Sprite(651, 52, TextureConstant::NONE_TEXTURE, infoPanel);
	infoPanel->itemShot->SetAnchor(0.5, 0.5);
	infoPanel->itemShot->SetScale(3, 3);




	group->AddGroup(infoPanel);
	return infoPanel;
}

HealthBar * CVAdd::UIPlayerHealthBar(double x, double y, ggEngine::Group* group)
{
	HealthBar *bar = new HealthBar(this->cvGame);
	ggEngine::Sprite* emptyHealthBar = this->add->Sprite(0, 0, TextureConstant::EMPTY_HEALTH_TEXTURE, bar);
	ggEngine::Sprite* healthBar = this->add->Sprite(0, 0, TextureConstant::FULL_HEALTH_PLAYER_TEXTURE, bar);
	bar->SetEmptyHealthBar(emptyHealthBar);
	bar->SetHealthBar(healthBar,16);
	bar->SetPosition(x, y);
	group->AddGroup(bar);
	return bar;
}

HealthBar * CVAdd::UIEnemyHealthBar(double x, double y, ggEngine::Group* group)
{
	HealthBar *bar = new HealthBar(this->cvGame);
	ggEngine::Sprite* emptyHealthBar = this->add->Sprite(0, 0, TextureConstant::EMPTY_HEALTH_TEXTURE, bar);
	ggEngine::Sprite* healthBar = this->add->Sprite(0, 0, TextureConstant::FULL_HEALTH_ENEMY_TEXTURE, bar);
	bar->SetEmptyHealthBar(emptyHealthBar);
	bar->SetHealthBar(healthBar, 16);
	bar->SetPosition(x, y);
	group->AddGroup(bar);
	return bar;
}

CVMap * CVAdd::LoadMap(const char * json, ggEngine::Group * group)
{
	CVMap *cvMap = new CVMap(this->cvGame);
	cvMap->BuildMap(json);
	group->AddGroup(cvMap);
	return cvMap;
}

SimonGroup * CVAdd::AddSimonGroup()
{
	return new SimonGroup(this->cvGame);
}

GameOverScreen * CVAdd::UIGameOverScreen(ggEngine::Group * group)
{
	GameOverScreen *goScreen = new GameOverScreen(this->cvGame);
	Style style;
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	int fontSize = 22;

	goScreen->heart = this->add->Sprite(394 - fontSize * 5, 420, TextureConstant::HEART_MINI_TEXTURE, goScreen);
	goScreen->heart->SetAnchor(0.5, 0.5);
	goScreen->heart->SetScale(3, 3);

	goScreen->gameOver = this->add->Text(384 - fontSize * 4, 291, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "GAME OVER", style, goScreen);
	goScreen->cont = this->add->Text(384 - fontSize * 3, 411, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "CONTINUE", style, goScreen);
	goScreen->end = this->add->Text(384 - fontSize * 3, 483, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "END", style, goScreen);

	goScreen->SetEventToggleHeart([this] {

	}, [this]{

	});
	goScreen->SetEnable(false);

	group->AddGroup(goScreen);
	return goScreen;
}