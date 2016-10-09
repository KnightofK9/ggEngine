#include "MenuState.h"
MenuState::MenuState(Game * game) :State(game)
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
	this->preload->Texture("menu-background", "Resource/MenuBackground.jpg");
}


void MenuState::Create()
{
	menuGroup = this->add->Group();
	background = this->add->Sprite(0, 0, "menu-background", menuGroup);
	background->SetAnchor(0, 0);
	background->SetWidth(WINDOW_WIDTH);
	background->SetHeight(WINDOW_HEIGHT);

}

void MenuState::Update()
{

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
