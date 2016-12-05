#include "CVAdd.h"
#include "TextureConstant.h"
#include "TypeEnum.h"
#include "CVState.h"
#include "CharacterConstant.h"

CVAdd::CVAdd(CVState* state , CVGame *cvgame):Add(cvgame)
{
	this->cvgame = cvgame;
	this->state = state;
}

CVAdd::~CVAdd()
{
}

Simon* CVAdd::CharSimon(double x, double y, int health, InfoPanel *infoPanel, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::SIMON_TEXTURE);
	Simon *simon = new Simon(this->cvgame, inf,infoPanel, 45, 40, 0,0, 130);
	simon->SetPosition(0, 0);

	group->AddDrawObjectToList(simon);

	this->camera->Follow(simon);

	return simon;
}

InfoPanel* CVAdd::UIInfoPanel(ggEngine::Group *group)
{

	InfoPanel *infoPanel = new InfoPanel(this->cvgame);
	Style style;
	int fontSize = 22;
	int margin = 20;
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	
#pragma region  First line
	infoPanel->score		= this->Text(	margin, margin, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "SCORE—", style, infoPanel);
	infoPanel->scorePoint	= this->Text(	10 + fontSize*6,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50, 
											"000000",
											style,
											infoPanel);

	infoPanel->time			= this->Text(	GAME_WIDTH/2 - fontSize*4,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"TIME",
											style,
											infoPanel);

	infoPanel->timePoint	= this->Text(	infoPanel->time->GetX() + fontSize*5, 
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											ggEngine::Helper::IntToString(infoPanel->GetTime(), 4),
											style,
											infoPanel);
	
	infoPanel->timeInfo = this->LoopInfinity(1000, [infoPanel] {
		if (infoPanel->GetTime() <= 0)
			infoPanel->StopTime();
		else {
			infoPanel->SetTime(infoPanel->GetTime() - 1);
			infoPanel->timePoint->SetText(ggEngine::Helper::IntToString(infoPanel->GetTime(), 4));
		}
	});
	infoPanel->StartTime();


	infoPanel->stage		= this->Text(	GAME_WIDTH - fontSize*10, 
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"STAGE",
											style,
											infoPanel);

	infoPanel->stagePoint	= this->Text(	infoPanel->stage->GetX() + fontSize*6,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"01",
											style,
											infoPanel);
#pragma endregion

#pragma region  Second line
	infoPanel->player		= this->Text(	margin,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"PLAYER",
											style,
											infoPanel);

	infoPanel->playerHealthBar = this->UIPlayerHealthBar(margin + fontSize*7, margin + fontSize, infoPanel);
	infoPanel->playerHealthBar->SetScale(1.3, 1.3);

	infoPanel->lifeIcon		= this->Sprite(	GAME_WIDTH / 2 + 110 + fontSize,
											margin + fontSize + 10,
											TextureConstant::LIFE_TEXTURE,
											infoPanel);
	infoPanel->lifeIcon->SetAnchor(0.5, 0.5);
	infoPanel->lifeIcon->SetScale(2.5, 2.5);
#pragma endregion

#pragma region  Third line
	infoPanel->enemy		= this->Text(	margin,
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
	infoPanel->life			= this->Text(	GAME_WIDTH / 2 + 100 + fontSize*2,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"-",
											style,
											infoPanel);

	infoPanel->lifePoint	= this->Text(	GAME_WIDTH/2 + 100 + fontSize*3,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"05",
											style,
											infoPanel);
	infoPanel->p			= this->Text(	GAME_WIDTH / 2 + 100 + fontSize,
											margin + fontSize * 2,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"P-",
											style,
											infoPanel);

	infoPanel->pPoint		= this->Text(	GAME_WIDTH/2 + 100 + fontSize*3,
											margin + fontSize * 2,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"03",
											style,
											infoPanel);

	infoPanel->itemBox		= this->Sprite(419, 75, "ItemBox", infoPanel);
	infoPanel->itemBox->SetAnchor(0.5, 0.5);
	infoPanel->itemBox->SetScale(3, 3);

	infoPanel->item = this->Sprite(408, 62, TextureConstant::NONE_TEXTURE, infoPanel);
	infoPanel->item->SetAnchor(0.5, 0.5);
	infoPanel->item->SetScale(3, 3);

	infoPanel->itemShot = this->Sprite(651, 52, TextureConstant::NONE_TEXTURE, infoPanel);
	infoPanel->itemShot->SetAnchor(0.5, 0.5);
	infoPanel->itemShot->SetScale(3, 3);

	group->AddGroup(infoPanel);
	return infoPanel;
}

HealthBar * CVAdd::UIPlayerHealthBar(double x, double y, ggEngine::Group* group)
{
	HealthBar *bar = new HealthBar(this->cvgame);
	ggEngine::Sprite* emptyHealthBar = this->Sprite(0, 0, TextureConstant::EMPTY_HEALTH_TEXTURE, bar);
	ggEngine::Sprite* healthBar = this->Sprite(0, 0, TextureConstant::FULL_HEALTH_PLAYER_TEXTURE, bar);
	bar->SetEmptyHealthBar(emptyHealthBar);
	bar->SetHealthBar(healthBar,16);
	bar->SetPosition(x, y);
	group->AddGroup(bar);
	return bar;
}

HealthBar * CVAdd::UIEnemyHealthBar(double x, double y, ggEngine::Group* group)
{
	HealthBar *bar = new HealthBar(this->cvgame);
	ggEngine::Sprite* emptyHealthBar = this->Sprite(0, 0, TextureConstant::EMPTY_HEALTH_TEXTURE, bar);
	ggEngine::Sprite* healthBar = this->Sprite(0, 0, TextureConstant::FULL_HEALTH_ENEMY_TEXTURE, bar);
	bar->SetEmptyHealthBar(emptyHealthBar);
	bar->SetHealthBar(healthBar, 16);
	bar->SetPosition(x, y);
	group->AddGroup(bar);
	return bar;
}