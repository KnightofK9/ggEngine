#include "InfoPanel.h"
InfoPanel::InfoPanel(DrawManager* drawManager) : ScreenGroup(drawManager)
{
}

InfoPanel::~InfoPanel()
{
}

void InfoPanel::Draw()
{
	//this->drawManager->DrawRectangleToWorld(0, 0, GAME_WIDTH, GAME_HEIGHT / 5.0f - GAME_HEIGHT / 40.0f, D3DCOLOR_RGBA(0, 0, 0, 255));
	this->drawManager->DrawRectangleToWorld(0, 0, GAME_WIDTH, GAME_HEIGHT/6, D3DCOLOR_RGBA(0, 0, 0, 255));

	ScreenGroup::Draw();
}

void InfoPanel::SetPlayerHealth(int health)
{
	this->playerHealthBar->SetHealth(health);
}

void InfoPanel::SetEnemyHealth(const int& health)
{
	this->enemyHealthBar->SetHealth(health);
}

void InfoPanel::SetLife(const int& point)
{
	this->lifePoint->SetText(ggEngine::Helper::IntToString(point, 2));
}

void InfoPanel::SetPoint(const int& point)
{
	this->pPoint->SetText(ggEngine::Helper::IntToString(point, 2));
}

void InfoPanel::SetState(const int& state)
{
	this->stagePoint->SetText(ggEngine::Helper::IntToString(state, 2));
}

void InfoPanel::SetScore(const int& score)
{
	this->scorePoint->SetText(ggEngine::Helper::IntToString(score, 6));
}

void InfoPanel::SetItemImage(SpriteInfo *spriteInfo)
{
	this->item->SetImage(spriteInfo);
}

void InfoPanel::StopTime()
{
	this->timeInfo->Stop();
}

void InfoPanel::StartTime()
{
	if (timeInfo != NULL && curTime > 0)
		this->timeInfo->Start();
}

void InfoPanel::SetTime(const int & time)
{
	this->curTime = time;
}
