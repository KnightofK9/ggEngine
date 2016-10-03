#include "PingPongState.h"
#include "Add.h"
#include "Preload.h"
#include "Game.h"
#include "Physics.h"
#include "Body.h"
#include "DXInput.h"
#include "Events.h"
#include "ColliderArg.h"
#include "EventManager.h"
#include "Text.h"

PingPongState::PingPongState(Game *game) :State(game)
{
}
PingPongState::~PingPongState()
{

}
void PingPongState::Init() {
	score1 = score2 = 0;
}
void PingPongState::Preload() {
	this->preload->Texture("bat", "Resource/bat.png");
	this->preload->Texture("ball", "Resource/ball.png");
}
void PingPongState::Create()
{
	group = this->add->Group();

#pragma region Ball
	ball = this->add->Sprite(0, 0, "ball",0, group);
	game->physics->EnablePhysics(ball);
	ball->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
		/*if (!e.blockDirection.up && !e.blockDirection.down)
		{
			srand(time(NULL));
			Vector velocity = { (rand() % 50)*1.0f, (rand() % 50)*1.0f };
			go->body->velocity = velocity;
		}*/
		if (e.blockDirection.left)
		{
			score2++;
			go->position.x = leftBat->GetPosition().x + leftBat->GetWidth();
			go->position.y = leftBat->GetPosition().y;
		}
		else if (e.blockDirection.right)
		{
			score1++;
			go->position.x = rightBat->GetPosition().x - rightBat->GetWidth();
			go->position.y = rightBat->GetPosition().y;
		}
	};

	ball->events->onCollide = [this](GameObject *go, ColliderArg e) {
		Vector velocity = go->body->velocity;
		if (e.blockDirection.left) velocity.x*= -1;
		else if (e.blockDirection.right) velocity.x*= -1;
		else if (e.blockDirection.up) velocity.y *= -1;
		else if (e.blockDirection.down) velocity.y *= -1;
		Vector n = e.normalSurfaceVector;
		go->body->velocity = velocity;
	};
	ball->body->CreateRectangleRigidBody(ball->GetWidth(), ball->GetHeight());
	ball->body->AddForce(5, Vector(50,50));
#pragma endregion Ball

	

#pragma region Bat
	leftBat = this->add->Sprite(WINDOW_WIDTH / 20.0, WINDOW_HEIGHT / 2.0, "bat", 0, group);
	leftBat->name = "Left Bat";
	leftBat->position.x = leftBat->GetWidth() / 2;
	game->physics->EnablePhysics(leftBat);
	leftBat->body->allowBounciness = false;
	leftBat->body->CreateRectangleRigidBody(leftBat->GetWidth(), leftBat->GetHeight());
	game->eventManager->EnableKeyBoardInput(leftBat);
	leftBat->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		if (e.isPress(DIK_W)) {
			if (!go->body->blocked.up)
				go->position.y -= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
		if (e.isPress(DIK_S)) {
			if (!go->body->blocked.down)
				go->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
	};

	rightBat = this->add->Sprite(WINDOW_WIDTH - leftBat->GetWidth() / 2, WINDOW_HEIGHT / 2.0, "bat", 0, group);
	rightBat->name = "Right Bat";
	game->physics->EnablePhysics(rightBat);
	rightBat->body->CreateRectangleRigidBody(rightBat->GetWidth(), rightBat->GetHeight());
	game->eventManager->EnableKeyBoardInput(rightBat);
	rightBat->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		if (e.isPress(DIK_UPARROW)) {
			if (!go->body->blocked.up)
				go->position.y -= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
		if (e.isPress(DIK_DOWNARROW)) {
			if (!go->body->blocked.down)
				go->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
	};
#pragma endregion Bat



#pragma region Others
	// Text
	Style style;
	textScore1 = this->add->Text(WINDOW_WIDTH / 2.0 - 50, WINDOW_HEIGHT / 2.0, std::to_string(score1), style, group);
	textScore2 = this->add->Text(WINDOW_WIDTH / 2.0 + 50, WINDOW_HEIGHT / 2.0, std::to_string(score2), style, group);

#pragma endregion Others
}
void PingPongState::Update()
{
	textScore1->SetText(std::to_string(score1));
	textScore2->SetText(std::to_string(score2));
}
void PingPongState::PreRender()
{
}
void PingPongState::Render()
{
	game->physics->CheckBound(leftBat, ball);
	game->physics->CheckBound(rightBat, ball);
	Debug::Log(game->frameRateReal);
}
void PingPongState::Pause()
{
}
void PingPongState::Resume()
{
}
void PingPongState::ShutDown()
{
}
