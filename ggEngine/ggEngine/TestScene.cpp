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
	this->preload->Sprite("girl", "Resource/girl.jpg");
}
void TestState::Create()
{
	this->test = 0;
	Group* group = this->add->Group();
	this->sprite1 = this->add->Sprite(50, 50, "default", NULL, group);
	this->sprite2 = this->add->Sprite(50, 50, "girl", NULL, group);
	//this->sprite3 = this->add->Sprite(50, 50, "default", NULL, group);
	this->sprite1->SetAnchor(0.5, 0.5);
	this->sprite2->SetAnchor(0.5, 0.5);
	this->sprite2->SetWidth(49);
	this->sprite2->SetHeight(47);
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