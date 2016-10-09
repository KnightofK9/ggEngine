#include "MenuState.h"
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
	//this->preload->Texture("singleBtnNormal", "Resource/1p.png");
	//this->preload->Texture("singleBtnHolver", "Resource/1p_b.png");
	//this->preload->Texture("multiBtnNormal", "Resource/2p.png");
	//this->preload->Texture("multiBtnHover", "Resource/2p_b.png");

	/*Load atas*/
	this->preload->Atlas("GameAtlas", "Resource/sprites.png", "Resource/sprites.xml");
}
void Switch(bool isSwitchToSingle) {
	isSingle = isSwitchToSingle;
	singleBtnHover->SetVisible(isSwitchToSingle);
	multiBtnHover->SetVisible(!isSwitchToSingle);
}

void MenuState::Create()
{
	groupMenu = this->add->Group();
	singleBtnNormal = this->add->Sprite(WINDOW_WIDTH / 2.0f - 300, WINDOW_HEIGHT / 2.0f + 200, "singleBtnNormal", groupMenu);
	singleBtnHover = this->add->Sprite(WINDOW_WIDTH / 2.0f - 300, WINDOW_HEIGHT / 2.0f + 200, "singleBtnHolver", groupMenu);
	multiBtnNormal = this->add->Sprite(WINDOW_WIDTH / 2.0f + 300, WINDOW_HEIGHT / 2.0f + 200, "multiBtnNormal", groupMenu);
	multiBtnHover = this->add->Sprite(WINDOW_WIDTH / 2.0f + 300, WINDOW_HEIGHT / 2.0f + 200, "multiBtnHover", groupMenu);
	multiBtnHover->SetVisible(false);



	Sprite* a = this->add->Sprite(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, "abc", groupMenu);
	groupText = this->add->Group();
	//Other
	Style style;
	style.fontColor = D3DCOLOR_ARGB(255, 100, 100, 100);
	Text *title = this->add->Text(WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0,"default",500,105, "PING", style, groupText);
	title->SetAnchor(0.7, 0.3);
	title->SetScale(1,3);

	Style style2;
	style2.fontColor = D3DCOLOR_ARGB(255, 30, 130, 30);
	style2.backgroundColor = D3DCOLOR_ARGB(255, 255, 255, 100);
	Text *subText = this->add->Text(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT - 50, "default",500,100, "Esc: Exit          Q: Enter", style2, groupText);
	subText->SetAnchor(0.5, 0.5);

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
		game->stateManager->Start("PingPongState", true, false);
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
