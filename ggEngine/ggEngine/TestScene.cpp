#include "TestState.h"
#include "Add.h"
#include "Preload.h"
#include "SpriteAnimation.h"
TestState::TestState(Game *game):State(game)
{
}
TestState::~TestState()
{
}
void TestState::Init(){

}
void TestState::Preload(){
	this->preload->Texture("kitty", "Resource/kitty.bmp");
}
void TestState::Create()
{
	this->test = 0;
	Group* group = this->add->Group();
	SpriteAnimation *sprite = this->add->SpriteAnimation(40,40,"kitty", 92, 60, group, 0);
	sprite->CreateAnimation("MoveLeft", 0, 5, true);
	sprite->CreateAnimation("MoveRight", 6, 11, true);
	sprite->PlayAnimation("MoveLeft");
	//this->sprite3->SetAnchor(0, 0);
	//sprite3->SetScale(2, 2);
	//sprite1->SetScale(2, 2);
	//this->sprite3->Destroy();
}
void TestState::Update()
{
	/*test += 10;
	this->sprite1->SetRotate(test);
	this->sprite2->SetRotate(test - 4);
	this->sprite3->SetRotate(test - 7);*/
}
void TestState::PreRender()
{
}
void TestState::Render()
{
}
void TestState::Pause()
{
}
void TestState::Resume()
{
}
void TestState::ShutDown()
{
}