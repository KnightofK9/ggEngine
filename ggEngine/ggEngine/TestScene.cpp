#include "TestState.h"
#include "Add.h"
#include "Preload.h"
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
	this->preload->Texture("girl", "Resource/girl.jpg");
}
void TestState::Create()
{
	this->test = 0;
	Group* group = this->add->Group();
	sprite1 = this->add->SpriteAnimation(500,500,"kitty", 92, 60, group, 0);
	sprite1->CreateAnimation("MoveLeft", 0, 5, true);
	sprite1->CreateAnimation("MoveRight", 6, 11, true);
	sprite1->PlayAnimation("MoveLeft");
	sprite2 = this->add->Sprite(400, 500, "girl",0,group);
	sprite2->SetWidth(40);
	sprite2->SetHeight(50);
	//this->sprite3->SetAnchor(0, 0);
	//sprite3->SetScale(2, 2);
	//sprite1->SetScale(2, 2);
	//this->sprite3->Destroy();
}
void TestState::Update()
{
	sprite1->SetX(sprite1->GetX() - 3);
	sprite2->SetX(sprite2->GetX() - 3);
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