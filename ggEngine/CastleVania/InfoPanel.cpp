#include "InfoPanel.h"
#include "CVGame.h"
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
	this->drawManager->DrawRectangleToWorld(0, 0, GAME_WIDTH, 145, D3DCOLOR_RGBA(0, 0, 0, 255));

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

TimeBasedEventInfo* InfoPanel::CountDown(int timeBegin, std::function<void(void)> onTimeUp)
{
	this->onTimeUp = onTimeUp;
	this->curTime = timeBegin;
	return this->timeInfo = this->cvGame->add->LoopInfinity(1000, [this] {
		if (this->curTime <= 0) {
			this->StopTime();
			this->onTimeUp();
		}
		else {
			this->SetTime(this->curTime - 1);
			this->timePoint->SetText(ggEngine::Helper::IntToString(this->curTime, 4));
		}
	});
}

void InfoPanel::StopTime()
{
	if (this->timeInfo != NULL)
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
