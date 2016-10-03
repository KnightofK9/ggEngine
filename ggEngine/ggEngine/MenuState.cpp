#include "MenuState.h"
#include "Add.h"
#include "Preload.h"
#include "Game.h"
#include "Physics.h"
#include "Body.h"
#include "DXInput.h"
#include "Events.h"
#include "ColliderArg.h"
#include "EventManager.h"
#include "Timer.h"
#include "Text.h"
#include "Input.h"
Sprite* singleBtnNormal;
Sprite* singleBtnHover;
Sprite* multiBtnNormal;
Sprite* multiBtnHover;
Group* groupMenu;
bool isSingle = true;
MenuState::MenuState(Game * game):State(game)
{
}

MenuState::~MenuState()
{
}

void MenuState::Init()
{
}

void MenuState::Preload()
{
	this->preload->Texture("singleBtnNormal", "Resource/1p.png");
	this->preload->Texture("singleBtnHolver", "Resource/1p_b.png");
	this->preload->Texture("multiBtnNormal", "Resource/2p.png");
	this->preload->Texture("multiBtnHover", "Resource/2p_b.png");
}
void Switch(bool isSwitchToSingle) {
	isSingle = isSwitchToSingle;
	singleBtnHover->SetVisible(isSwitchToSingle);
	multiBtnHover->SetVisible(!isSwitchToSingle);
}

void MenuState::Create()
{
	groupMenu = this->add->Group();
	singleBtnNormal = this->add->Sprite(WINDOW_WIDTH / 2.0f - 300, WINDOW_HEIGHT / 2.0f + 200, "singleBtnNormal", 0, groupMenu);
	singleBtnHover = this->add->Sprite(WINDOW_WIDTH / 2.0f - 300, WINDOW_HEIGHT / 2.0f + 200, "singleBtnHolver", 0, groupMenu);
	multiBtnNormal = this->add->Sprite(WINDOW_WIDTH / 2.0f + 300, WINDOW_HEIGHT / 2.0f + 200, "multiBtnNormal", 0, groupMenu);
	multiBtnHover = this->add->Sprite(WINDOW_WIDTH / 2.0f + 300, WINDOW_HEIGHT / 2.0f + 200, "multiBtnHover", 0, groupMenu);
	multiBtnHover->SetVisible(false);

	//Other
	Style style;
	style.fontSize = 100;
	style.fontColor = D3DCOLOR_XRGB(255,255,255);
	style.font = "Segoe UI Black";
	style.fontVariant = "bold";
	style.fontWeight = 1;
	this->add->Text(WINDOW_WIDTH/2.0 - 230, WINDOW_HEIGHT/2.0 - 50, "PING PONG", style, groupMenu);

	Style style2;
	style.fontSize = 36;
	style.fontColor = D3DCOLOR_XRGB(30, 30, 30);
	style.font = "Segoe UI";
	style.fontWeight = 1;
	this->add->Text(WINDOW_WIDTH / 2.0 - 180, WINDOW_HEIGHT - 50, "Esc: Exit          Q: Enter", style, groupMenu);
}

void MenuState::Update()
{
	if(game->GetInput()->KeyDown(DIK_LEFTARROW)) {
		Switch(true);
	}
	else if (game->GetInput()->KeyDown(DIK_RIGHTARROW)) {
		Switch(false);
	}
	else if (game->GetInput()->KeyDown(DIK_RETURN)) {
		game->stateManager->Start("PingPongState", true, true);
	}
}

void MenuState::PreRender()
{
}

void MenuState::Render()
{
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::ShutDown()
{
}