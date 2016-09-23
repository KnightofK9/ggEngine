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

}
void TestState::Create()
{
	this->test = 0;
	Group* group = this->add->Group();
	this->sprite1 = this->add->Sprite(30, 30, "default", NULL, group);
	this->sprite2 = this->add->Sprite(30, 30, "default", NULL, group);
	this->sprite3 = this->add->Sprite(30, 30, "default", NULL, group);
	sprite3->SetScale(10, 20);
	sprite2->SetScale(20, 10);
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