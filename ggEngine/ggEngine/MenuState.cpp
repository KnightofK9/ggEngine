#include "MenuState.h"
Sprite* singleBtnNormal;
Sprite* singleBtnHover;
Sprite* multiBtnNormal;
Sprite* multiBtnHover;
Sprite* menuBackground;
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
	this->preload->Texture("singleBtnNormal", "Resource/PingPong/1p.png");
	this->preload->Texture("singleBtnHolver", "Resource/PingPong/1p_b.png");
	this->preload->Texture("multiBtnNormal", "Resource/PingPong/2p.png");
	this->preload->Texture("multiBtnHover", "Resource/PingPong/2p_b.png");
	this->preload->Texture("menuBackground", "Resource/PingPong/bg.png");
	/*Load atas*/
	//this->preload->Atlas("GameAtlas", "Resource/sprites.png", "Resource/sprites.xml");

}
void Switch(bool isSwitchToSingle) {
	isSingle = isSwitchToSingle;
	singleBtnHover->SetVisible(isSwitchToSingle);
	multiBtnHover->SetVisible(!isSwitchToSingle);
}

void MenuState::Create()
{
	sound = new Sound(game->hWnd, "Resource/Sound/start.wav", SoundType_Sound, true);
	sound->Start();

	groupMenu = this->add->Group();
	menuBackground = this->add->Sprite(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, "menuBackground", groupMenu);
	menuBackground->SetScale(Vector(0.8, 0.8));
	singleBtnNormal = this->add->Sprite(300, WINDOW_HEIGHT / 2.0f - 50, "singleBtnNormal", groupMenu);
	singleBtnHover = this->add->Sprite(300, WINDOW_HEIGHT / 2.0f - 50, "singleBtnHolver", groupMenu);
	multiBtnNormal = this->add->Sprite(300, WINDOW_HEIGHT / 2.0f + 50, "multiBtnNormal", groupMenu);
	multiBtnHover = this->add->Sprite(300, WINDOW_HEIGHT / 2.0f + 50, "multiBtnHover", groupMenu);
	multiBtnHover->SetVisible(false);



	//Sprite* a = this->add->Sprite(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, "abc", groupMenu);
	//groupText = this->add->Group();
	////Other
	//Style style;
	//style.fontColor = D3DCOLOR_ARGB(255, 100, 100, 100);
	//Text *title = this->add->Text(WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0,"default",500,105, "PING", style, groupText);
	//title->SetAnchor(0.7, 0.3);
	//title->SetScale(1,3);

	//Style style2;
	//style2.fontColor = D3DCOLOR_ARGB(255, 30, 130, 30);
	//style2.backgroundColor = D3DCOLOR_ARGB(255, 255, 255, 100);
	//Text *subText = this->add->Text(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT - 50, "default",500,100, "Esc: Exit          Q: Enter", style2, groupText);
	//subText->SetAnchor(0.5, 0.5);

}

void MenuState::Update()
{
	if(game->GetInput()->KeyDown(DIK_UP)) {
		Switch(true);
	}
	else if (game->GetInput()->KeyDown(DIK_DOWN)) {
		Switch(false);
	}
	else if (game->GetInput()->KeyDown(DIK_RETURN)) {
		Sound *enterKeySound = new Sound(game->hWnd, "Resource/Sound/ping.wav");
		enterKeySound->Start();
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
	if (sound != NULL)
	{
		delete sound;
		sound = NULL;
	}
}
