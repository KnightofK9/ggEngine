#include "MenuState.h"
#include <fstream>
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
	menuBackground = this->add->Sprite(GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, "menuBackground", groupMenu);
	menuBackground->SetScale(Vector(0.8, 0.8));
	singleBtnNormal = this->add->Sprite(300, GAME_HEIGHT / 2.0f - 50, "singleBtnNormal", groupMenu);
	singleBtnHover = this->add->Sprite(300, GAME_HEIGHT / 2.0f - 50, "singleBtnHolver", groupMenu);
	multiBtnNormal = this->add->Sprite(300, GAME_HEIGHT / 2.0f + 50, "multiBtnNormal", groupMenu);
	multiBtnHover = this->add->Sprite(300, GAME_HEIGHT / 2.0f + 50, "multiBtnHover", groupMenu);
	multiBtnHover->SetVisible(false);
	this->add->Tween(singleBtnNormal->position.y, singleBtnNormal->position.y - 200, 5000, Easing::easeOutQudouble)->Start();
	this->add->Tween(singleBtnNormal->position.x, singleBtnNormal->position.x + 500, 5000, Easing::easeOutCirc)->SetOnFinish([this]() {
		this->add->Tween(singleBtnNormal->position.x, singleBtnNormal->position.x - 500, 5000, Easing::easeInCubic)->Start();
		this->add->Tween(singleBtnNormal->position.y, singleBtnNormal->position.y + 200, 5000, Easing::easeInOutCubic)->Start();
	})->Start();
	this->add->Tween(singleBtnHover->position.y, singleBtnHover->position.y + 200, 1000, Easing::linearTween)->Start();
	this->add->Tween(singleBtnHover->position.x, singleBtnHover->position.x - 500, 1000, Easing::linearTween)->SetOnFinish([this]() {
		this->add->Tween(singleBtnHover->position.x, singleBtnHover->position.x + 500, 2000, Easing::linearTween)->Start();
		this->add->Tween(singleBtnHover->position.y, singleBtnHover->position.y - 200, 2000, Easing::linearTween)->Start();
	})->Start();

	this->add->Tween(multiBtnNormal->position.y, multiBtnNormal->position.y - 200, 5000, Easing::easeInExpo)->Start();
	this->add->Tween(multiBtnNormal->position.x, multiBtnNormal->position.x + 500, 5000, Easing::easeInOutCubic)->SetOnFinish([this]() {
		this->add->Tween(multiBtnNormal->position.x, multiBtnNormal->position.x - 500, 5000, Easing::easeInOutQuart)->Start();
		this->add->Tween(multiBtnNormal->position.y, multiBtnNormal->position.y + 200, 5000, Easing::easeOutSine)->Start();
	})->Start();
	this->add->Tween(multiBtnHover->position.y, multiBtnHover->position.y + 200, 1000, Easing::linearTween)->Start();
	this->add->Tween(multiBtnHover->position.x, multiBtnHover->position.x - 500, 1000, Easing::linearTween)->SetOnFinish([this]() {
		this->add->Tween(multiBtnHover->position.x, multiBtnHover->position.x + 500, 2000, Easing::linearTween)->Start();
		this->add->Tween(multiBtnHover->position.y, multiBtnHover->position.y - 200, 2000, Easing::linearTween)->Start();
	})->Start();
	//Sprite* a = this->add->Sprite(GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f, "abc", groupMenu);
	//groupText = this->add->Group();
	////Other
	//Style style;
	//style.fontColor = D3DCOLOR_ARGB(255, 100, 100, 100);
	//Text *title = this->add->Text(GAME_WIDTH/2.0, GAME_HEIGHT/2.0,"default",500,105, "PING", style, groupText);
	//title->SetAnchor(0.7, 0.3);
	//title->SetScale(1,3);

	//Style style2;
	//style2.fontColor = D3DCOLOR_ARGB(255, 30, 130, 30);
	//style2.backgroundColor = D3DCOLOR_ARGB(255, 255, 255, 100);
	//Text *subText = this->add->Text(GAME_WIDTH / 2.0, GAME_HEIGHT - 50, "default",500,100, "Esc: Exit          Q: Enter", style2, groupText);
	//subText->SetAnchor(0.5, 0.5);
	//Box *box = new Box(1, 2, 3, 4, 5, 6);
	//std::ofstream ofs("box_backup");
	//{
	//	boost::archive::text_oarchive oa(ofs);
	//	// write class instance to archive
	//	oa << box;
	//	// archive and stream closed when destructors are called
	//}

	//box = new Box(0, 0, 0, 0, 0, 0);
	//{
	//	// create and open an archive for input
	//	std::ifstream ifs("box_backup");
	//	boost::archive::text_iarchive ia(ifs);
	//	// read class state from archive
	//	ia >> box;
	//	// archive and stream closed when destructors are called
	//}
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
