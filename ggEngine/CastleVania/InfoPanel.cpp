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

	Group::Draw();
}
