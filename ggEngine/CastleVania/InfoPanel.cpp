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
	//this->playerHealthBar->
}

void InfoPanel::SetEnemyHealth(int health)
{
}

void InfoPanel::SetLife(int point)
{
	this->lifePoint->SetText(ggEngine::Helper::IntToString(point, 2));
}

void InfoPanel::SetPoint(int point)
{
	this->pPoint->SetText(ggEngine::Helper::IntToString(point, 2));
}

void InfoPanel::SetState(int state)
{
	this->stagePoint->SetText(ggEngine::Helper::IntToString(state, 2));
}

void InfoPanel::SetScore(int score)
{
	this->scorePoint->SetText(ggEngine::Helper::IntToString(score, 6));
}
