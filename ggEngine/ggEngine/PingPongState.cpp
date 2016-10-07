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
#include "Input.h"
extern bool isSingle;
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
	ball = this->add->Sprite(WINDOW_WIDTH /2.0, WINDOW_HEIGHT / 2.0, "ball",0, group);
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
		if (e.blockDirection.left) go->position.x += 5;
		else if (e.blockDirection.right) go->position.x -= 5;
		else if (e.blockDirection.up) go->position.y += 5;
		else if (e.blockDirection.down) go->position.y -= 5;
		Vector n = e.normalSurfaceVector;
		Vector d = go->body->velocity;
		Vector r = d - 2 * (Vector::DotProduct(d, n))*n;
		go->body->velocity = r;
	};
	ball->body->CreateRectangleRigidBody(ball->GetWidth(), ball->GetHeight());
	ball->body->AddForce(30, Vector(1,0));
#pragma endregion Ball

	

#pragma region Bat
	int distant = 100;
	leftBat = this->add->Sprite(WINDOW_WIDTH/2.0, WINDOW_HEIGHT / 2.0, "bat", 0, group);
	leftBat->name = "Left Bat";
	leftBat->position.x = leftBat->GetWidth() / 2 + 50;
	game->physics->EnablePhysics(leftBat);
	leftBat->body->allowBounciness = false;
	leftBat->body->CreateRectangleRigidBody(leftBat->GetWidth(), leftBat->GetHeight());
	game->eventManager->EnableKeyBoardInput(leftBat);
	if (!isSingle) {
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
	}

	rightBat = this->add->Sprite(WINDOW_WIDTH - leftBat->GetWidth() / 2 - 50, WINDOW_HEIGHT / 2.0, "bat", 0, group);
	rightBat->name = "Right Bat";
	game->physics->EnablePhysics(rightBat);
	rightBat->body->CreateRectangleRigidBody(rightBat->GetWidth(), rightBat->GetHeight());
	if (!isSingle) {
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
	}
	leftBat->SetScale(1, 0.5);
	rightBat->SetScale(1, 0.5);
#pragma endregion Bat



#pragma region Others
	// Text
	Style style;
	style.fontSize = 80;
	style.fontColor = D3DCOLOR_ARGB(255,120, 180, 210);
	style.font = "Segoe UI Black";
	style.fontVariant = "bold";
	style.fontWeight = 1;
	textScore1 = this->add->Text(WINDOW_WIDTH / 2.0 - 80, WINDOW_HEIGHT/2.0,200,200, std::to_string(score1), style, group);
	textScore1->SetAnchor(0.5, 0.5);
	textScore2 = this->add->Text(WINDOW_WIDTH / 2.0 + 80, WINDOW_HEIGHT/2.0,200,200, std::to_string(score2), style, group);
	textScore2->SetAnchor(0.5, 0.5);

	Style style2;
	style.fontSize = 36;
	style.fontColor = D3DCOLOR_ARGB(255, 30, 30, 30);
	style.font = "Segoe UI Black";
	style.fontWeight = 1;
	this->add->Text(150, 50,200,200, "W-S", style, group);
	this->add->Text(WINDOW_WIDTH - 150, 50,200,200, "Up-Down", style, group);

#pragma endregion Others
}
void PingPongState::Update()
{
	textScore1->SetText(std::to_string(score1));
	textScore2->SetText(std::to_string(score2));
	if (isSingle) {
		if (ball->position.y<rightBat->position.y) rightBat->position.y -= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		else if (ball->position.y>rightBat->position.y) {
			rightBat->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
		if (ball->position.y<leftBat->position.y) leftBat->position.y -= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		else if (ball->position.y>leftBat->position.y) {
			leftBat->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
	}
	if (game->GetInput()->KeyDown(DIK_Q)) {
		game->stateManager->Start("MenuState", true, true);
	}
}
void PingPongState::PreRender()
{
}
void PingPongState::Render()
{
	game->physics->CheckBound(leftBat, ball);
	game->physics->CheckBound(rightBat, ball);
	ball->body->Render();
	leftBat->body->Render();
	rightBat->body->Render();
	//Debug::Log(game->frameRateReal);
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
