#include "StoryState.h"

StoryState::StoryState(CVGame * game) : CVState(game)
{
}

StoryState::~StoryState()
{
}

void StoryState::Init()
{
	this->preload->Texture(TextureConstant::SIMON_TEXTURE, TextureConstant::SIMON_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::BAT_ANIM_TEXTURE, TextureConstant::BAT_ANIM_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::HELICOPTER_TEXTURE, TextureConstant::HELICOPTER_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::INTRO_BG_TEXTURE, TextureConstant::INTRO_BG_TEXTURE_PATH);

}

void StoryState::Preload()
{
}

void StoryState::Create()
{
	this->cvgame->camera->SetPoint(128, 112);
	this->cvgame->camera->SetScale(3, 3);

	Group *group = this->add->Group();
	this->bg = this->add->Sprite(128, 133, TextureConstant::INTRO_BG_TEXTURE, group);
	this->bg->SetAnchor(0.5, 0.5);

	this->helicopter = this->add->Sprite(73, 133, TextureConstant::HELICOPTER_TEXTURE, group);
	this->helicopter->SetAnchor(0.5, 0.5);

	this->bat1 = this->add->SpriteAnimation(128, 132, TextureConstant::BAT_ANIM_TEXTURE, 17, 16, group, 0, 2, 300);
	this->bat1->SetAnchor(0.5, 0.5);
	this->bat1->CreateAnimation("bat1", 0, 1, true);
	this->bat1->PlayAnimation("bat1");

	this->bat2 = this->add->SpriteAnimation(128, 132, TextureConstant::BAT_ANIM_TEXTURE, 17, 16, group, 0, 2, 300);
	this->bat2->SetAnchor(0.5, 0.5);
	this->bat2->CreateAnimation("bat2", 0, 1, true);
	this->bat2->PlayAnimation("bat2");

	this->simon = this->add->SpriteAnimation(224, 182, TextureConstant::SIMON_TEXTURE, 45, 40, group, 0, 25, 200);
	this->simon->SetAnchor(0.5, 0.5);
	this->simon->CreateAnimation("walk", 0, 3, true);
	this->simon->CreateAnimation("back", 19, 19, false);

	this->simon->PlayAnimation("walk");
	this->add->LoopInfinity(0, [this] {
		this->simon->SetPosition(this->simon->GetPosition().x - 1, this->simon->GetPosition().y);
	})->Start();

	//this->cvAdd->TimeOut(1000, [this] {
	//	this->simon->SetPosition(this->simon->GetPosition().x, this->simon->GetPosition().y);
	//	this->simon->PlayAnimation("back");
	//})->Start();

	
	

}

void StoryState::Update()
{
}

void StoryState::PreRender()
{
}

void StoryState::Render()
{
}

void StoryState::Pause()
{
}

void StoryState::Resume()
{
}

void StoryState::ShutDown()
{
}
