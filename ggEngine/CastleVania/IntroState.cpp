#include "IntroState.h"

IntroState::IntroState(CVGame *game) : CVState(game)
{
}
IntroState::~IntroState()
{
}
void IntroState::Init() {

}
void IntroState::Preload() {
	this->cvPreload->Texture("menu_bg", "Resource/Resources/MenuScene/menu_bg.png");
	this->cvPreload->Texture("menu_anim", "Resource/Resources/MenuScene/menu_anim.png");
	this->cvPreload->Font(TextureConstant::GAME_FONT_TEXTURE, TextureConstant::GAME_FONT_NAME, TextureConstant::GAME_FONT_TEXTURE_PATH, 10);

}
void IntroState::Create()
{
	Group* group = this->cvAdd->Group();
	this->menu_bg = this->cvAdd->Sprite(128, 112, "menu_bg", group);
	this->menu_bg->SetAnchor(0.5, 0.5);
	
	this->cvgame->camera->RegisterControl(CameraControl_MoveUp, DIK_W);
	this->cvgame->camera->RegisterControl(CameraControl_MoveDown, DIK_S);
	this->cvgame->camera->RegisterControl(CameraControl_MoveLeft, DIK_A);
	this->cvgame->camera->RegisterControl(CameraControl_MoveRight, DIK_D);
	this->cvgame->camera->RegisterControl(CameraControl_ZoomIn, DIK_1);
	this->cvgame->camera->RegisterControl(CameraControl_ZoomOut, DIK_2);
	this->cvgame->camera->SetPoint(128, 112);
	this->cvgame->camera->SetScale(3, 3);


	this->menu_anim = this->cvAdd->SpriteAnimation(220, 125, "menu_anim", 72, 58, group, 0, 15, 100);
	cvgame->eventManager->EnableSpriteAnimationEvent(menu_anim);
	this->menu_anim->CreateAnimation("anim", 0, 13, false);
	menu_anim->events->onAnimationCompleted = [this](GameObject *go, AnimationArg e) {
		g_debug.Log("Animation " + e.animationName + " completed. ");
	};
	this->menu_anim->PlayAnimation("anim");
	this->menu_anim->SetAnchor(0.5, 0.5);


	Style style;
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	int fontSize = 10;

	this->push = this->cvAdd->Text(128 - fontSize*7, 120, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "PUSH START KEY", style, group);
	//this->push
	//this->year = 


}
void IntroState::Update()
{

}
void IntroState::PreRender()
{
}
void IntroState::Render()
{

}
void IntroState::Pause()
{
}
void IntroState::Resume()
{
}
void IntroState::ShutDown()
{

}