#include "TestState.h"
#include "Add.h"
#include "Preload.h"
#include "Game.h"
#include "Physics.h"
#include "Body.h"
#include "DXInput.h"
#include "Events.h"
#include "ColliderArg.h"
#include "EventManager.h"
#include "Timer.h"
#include "Text.h"
#include "Input.h"
SpriteAnimation *character;
Group *group;
const float charMoveSpeed = 10.0f;
const float jumpForce = 5.0f;
const float jumpTime = 500;

Timer jumpTimer;
TestState::TestState(Game *game):State(game)
{
}
TestState::~TestState()
{
}
void TestState::Init(){

}
void TestState::Preload(){
	this->preload->Texture("character", "Resource/char.png");
}
void TestState::Create()
{
	group = this->add->Group();
	character = this->add->SpriteAnimation(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, "character", 32, 48, group);
	character->CreateAnimation("down", 0, 3, false);
	character->CreateAnimation("left", 4, 7, false);
	character->CreateAnimation("right", 8, 11, false);
	character->CreateAnimation("up", 12, 15, false);
	game->physics->EnablePhysics(character);
	character->body->CreateRectangleRigidBody(32, 48);
	character->body->allowGravity = true;
	character->body->allowBounciness = false;
	character->body->allowWorldBlock = true;
	game->eventManager->EnableKeyBoardInput(character);
	jumpTimer.reset();
	character->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		SpriteAnimation  *current = dynamic_cast<SpriteAnimation*>(go);
		if (current != NULL) {
			float time = game->logicTimer.getDeltaTime();
			if (e.isPress(DIK_A)) {
				character->NextAnimationFrame("left");
				if (character->body->velocity.x > 0) character->body->velocity.x = 0;
				character->body->velocity.x -= charMoveSpeed* time;
			}
			if (e.isPress(DIK_D)) {
				character->NextAnimationFrame("right");
				if (character->body->velocity.x < 0) character->body->velocity.x = 0;
				character->body->velocity.x += charMoveSpeed*time;
			}
			if (e.isPress(DIK_SPACE)) {
				if (jumpTimer.stopwatch(jumpTime)) {
					character->body->velocity.y = 0;
					character->body->AddForce(jumpForce, Vector(0, -1));
				}
				
			}
		}
	};
}
void TestState::Update()
{
	
}
void TestState::PreRender()
{
}
void TestState::Render()
{
	//character->body->Render();
	

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

