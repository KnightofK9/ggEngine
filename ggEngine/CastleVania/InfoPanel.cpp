#include "InfoPanel.h"
#include "CVGame.h"
#include "Constant.h"
#include "AudioManager.h"

InfoPanel::InfoPanel(CVGame *cvGame) : ScreenGroup(cvGame)
{
	this->cvGame = cvGame;
}

InfoPanel::~InfoPanel()
{
}

void InfoPanel::Draw()
{
	//this->drawManager->DrawRectangleToWorld(0, 0, GAME_WIDTH, GAME_HEIGHT / 5.0f - GAME_HEIGHT / 40.0f, D3DCOLOR_RGBA(0, 0, 0, 255));
	this->drawManager->DrawRectangleToWorld(0, 0, Constant::UI_INFO_PANEL_BACKGROUND_WIDTH, Constant::UI_INFO_PANEL_BACKGROUND_HEIGHT, D3DCOLOR_RGBA(0, 0, 0, 255));

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

void InfoPanel::SetHeartPoint(const int& point)
{
	this->heartPoint->SetText(ggEngine::Helper::IntToString(point, 2));
}

void InfoPanel::SetPPoint(const int& point)
{
	this->pPoint->SetText(ggEngine::Helper::IntToString(point, 2));
}

void InfoPanel::SetStatePoint(const int& state)
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

TimeBasedEventInfo* InfoPanel::CountDown(int maxTime, std::function<void(void)> onTimeOut)
{
	this->onTimeUp = onTimeOut;
	this->maxTime = maxTime + 1;
	return this->timeInfo = this->cvGame->add->Loop(1000, this->maxTime + 1, [this] {
		this->maxTime = this->timeInfo->numberOfLoops - 1;
		if (this->maxTime <= 0) {
			this->StopCountDownTime();
			this->onTimeUp();
		}

		if (this->maxTime <= 30
			&& this->maxTime > 0) {
			this->cvGame->audioManager->clockTickSound->Play();
		}
		this->timePoint->SetText(ggEngine::Helper::IntToString(this->maxTime, 4));
	});
}

void InfoPanel::StopCountDownTime()
{
	if (this->timeInfo != NULL)
		this->timeInfo->Stop();
}

void InfoPanel::StartCountDownTime()
{
	if (timeInfo != NULL && maxTime > 0)
		this->timeInfo->Start();
}

void InfoPanel::SetTime(const int & time)
{
	this->maxTime = time;
	this->timePoint->SetText(ggEngine::Helper::IntToString(this->maxTime, 4));
}
