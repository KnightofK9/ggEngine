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
	this->preload->Texture("menu_bg", "Resource/Resources/MenuScene/menu_bg.png");
	this->preload->Texture("menu_anim", "Resource/Resources/MenuScene/menu_anim.png");
	this->preload->Font(TextureConstant::GAME_FONT_TEXTURE, TextureConstant::GAME_FONT_NAME, TextureConstant::GAME_FONT_TEXTURE_PATH, 22);
	this->preload->Audio("audio", "defaultAudio.wav");

}
void IntroState::Create()
{
	Group* group = this->add->Group();
	this->menu_bg = this->add->Sprite(128, 112, "menu_bg", group);
	this->menu_bg->SetAnchor(0.5, 0.5);
	this->audio = this->add->Audio("audio");
	
	
	/*this->cvgame->camera->RegisterControl(CameraControl_MoveUp, DIK_W);
	this->cvgame->camera->RegisterControl(CameraControl_MoveDown, DIK_S);
	this->cvgame->camera->RegisterControl(CameraControl_MoveLeft, DIK_A);
	this->cvgame->camera->RegisterControl(CameraControl_MoveRight, DIK_D);
	this->cvgame->camera->RegisterControl(CameraControl_ZoomIn, DIK_1);
	this->cvgame->camera->RegisterControl(CameraControl_ZoomOut, DIK_2);*/


	this->cvgame->camera->SetPoint(128, 112);
	this->cvgame->camera->SetScale(3, 3);


	this->menu_anim = this->add->SpriteAnimation(220, 125, "menu_anim", 72, 58, group, 0, 15, 100);
	this->add->MoveBy(this->menu_anim, Vector(50, 100), 4000)->SetOnFinish([this]() {
		this->add->MoveTo(this->menu_anim, Vector(12, 125), 4000)->Start();
	})->Start();
	this->cvgame->eventManager->EnableSpriteAnimationEvent(menu_anim);
	this->menu_anim->CreateAnimation("batFly", 0, 13, false)->SetOnCompleted([this](Animator* animator) {
		animator->spriteAnimation->PlayAnimation("batFlyLoop");
	});
	this->menu_anim->CreateAnimation("batFlyLoop", 12, 13, true);
	//this->menu_anim->events->onAnimationCompleted = [this](GameObject *go, AnimationArg e) {
	//	e.animator->spriteAnimation->PlayAnimation("batFlyLoop");
	//};
	this->menu_anim->PlayAnimation("batFly");
	this->menu_anim->SetAnchor(0.5, 0.5);


	//============== Text =======================
	Style style;
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	int fontSize = 22;

	//384 = 128*3
	ScreenGroup *textGroup = this->add->ScreenGroup();
	this->push = this->add->Text(384 - fontSize*7, 384, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "PUSH START KEY", style, textGroup);
	this->cvgame->eventManager->EnableKeyBoardInput(this->push);
	this->push->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		Text  *current = dynamic_cast<Text*>(go);
		if (current != NULL) {
			if (e.isPress(DIK_RETURN) && isKeyPressed == false) {
				isKeyPressed = true;
				this->add->LoopInfinity(150, [this]() {
					this->push->SetVisible(!this->push->IsVisible());
				})->Start();

				this->audio->Play();

				this->add->TimeOut(1200, [this]() {
					if (this->cvgame->stateManager->GetCurrentState() == this)
						this->cvgame->stateManager->Start("TestStateCastleVania", true, true);
				})->Start();
			}}};
	this->year		= this->add->Text(384 - fontSize * 7,	456, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "TM AND © 1987", style, textGroup);
	this->coLTD		= this->add->Text(384 - fontSize * 12, 456 + fontSize, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "KONAMI INDUSTRY CO.,LTD.", style, textGroup);
	this->licenceBy = this->add->Text(384 - fontSize * 5, 456 + fontSize*2, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "LICENSED BY", style, textGroup);
	this->INC		= this->add->Text(384 - fontSize * 12, 456 + fontSize*3, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "NINTENDO OF AMERICA INC.", style, textGroup);
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


void IntroState::ChangeState()
{
	
}