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
SpriteAnimation *sprite1;
SpriteAnimation *sprite4;
Sprite *sprite2;
Sprite *sprite3;
float test = 0.01f;
Sprite *spriteBat2;
Sprite *background;
float MoveSpeedPerSec = 100.0f;
Timer shootTimer;
Group* group;
std::list<Sprite*> ballList;
float shootTime = 1000.0f;
Sprite *ball;
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
	this->preload->Texture("bat", "Resource/bat.png");
	this->preload->Texture("ball", "Resource/ball.png");
}
void TestState::Create()
{
	group = this->add->Group();
	//background = this->add->Sprite(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, "girl", 0, group);
	//background->SetWidth(WINDOW_WIDTH);
	//background->SetHeight(WINDOW_HEIGHT);
	CreateBall(Vector(50,50) , Vector(3, 4));
	//sprite2 = this->add->Sprite(20, 20, "ball", 0, group);
	//game->physics->EnablePhysics(sprite2);
	//sprite2->events->onCollide = [this](GameObject *go, ColliderArg e){
	//	if (e.blockDirection.left) go->position.x += 5;
	//	else if (e.blockDirection.right) go->position.x -= 5;
	//	else if (e.blockDirection.up) go->position.y += 5;
	//	else if (e.blockDirection.down) go->position.y -= 5;
	//	Vector n = e.normalSurfaceVector;
	//	Vector d = go->body->velocity;
	//	Vector r = d - 2 * (Vector::DotProduct(d, n))*n;
	//	go->body->velocity = r;


	//};
	////sprite2->body->CreateCircleRigidBody(sprite2->GetWidth() / 2);
	//sprite2->body->CreateRectangleRigidBody(sprite2->GetWidth(), sprite2->GetHeight());
	//sprite2->body->AddForce(5 , Vector(3, 4));
	/*Sprite3*/
	sprite3 = this->add->Sprite(WINDOW_WIDTH / 20.0, WINDOW_HEIGHT / 2.0, "bat", 0, group);
	sprite3->name = "Left Bat";
	sprite3->position.x = sprite3->GetWidth() / 2;
	game->physics->EnablePhysics(sprite3);
	sprite3->body->allowBounciness = false;
	sprite3->body->CreateRectangleRigidBody(sprite3->GetWidth(), sprite3->GetHeight());
	game->eventManager->EnableKeyBoardInput(sprite3);
	sprite3->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		float height = dynamic_cast<Sprite*>(go)->GetHeight();
		if (e.isPress(DIK_UPARROW)) {
			if(!go->body->blocked.up)
				go->position.y -= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
		if (e.isPress(DIK_DOWNARROW)) {
			if (!go->body->blocked.down)
			go->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}
	/*	if (e.isPress(DIK_SPACE)) {
			if (shootTimer.stopwatch(shootTime)) {
				Vector position = go->position;
				position.x += 50;
				CreateBall(position);
			}
		}*/
	};
	//sprite3->SetVisible(false);


	sprite3->SetScale(1, 0.5);

	spriteBat2 = this->add->Sprite(WINDOW_WIDTH - sprite3->GetWidth()/2, WINDOW_HEIGHT / 2.0, "bat", 0, group);
	spriteBat2->name = "Right Bat";
	game->physics->EnablePhysics(spriteBat2);
	spriteBat2->body->CreateRectangleRigidBody(spriteBat2->GetWidth(), spriteBat2->GetHeight());
	spriteBat2->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
		if (e.blockDirection.up || e.blockDirection.down) {
			test *= -1;
		}
	};
	Style style;
	Text *text = this->add->Text(WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0, "Diem so", style, group);

	//sprite1 = this->add->SpriteAnimation(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0,"kitty", 92, 60, group, 0);
	//sprite1 = this->add->SpriteAnimation(0, 0, "kitty", 92, 60, group, 0);
	//sprite4 = this->add->SpriteAnimation(WINDOW_WIDTH - 50, 50, "kitty", 92, 60, group, 0);
	//sprite2 = this->add->Sprite(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, "default", 0, group);
	//sprite2->SetAnchor(0, 0);
	//sprite3 = this->add->Sprite(1, 0, "default", 0, group);
	//sprite1->CreateAnimation("MoveLeft", 0, 5, true);
	//sprite1->CreateAnimation("MoveRight", 6, 11, true);
	//sprite4->CreateAnimation("MoveLeft", 0, 5, true);
	//sprite4->CreateAnimation("MoveRight", 6, 11, true);
	//sprite1->SetScale(1.3, 1.4);
	//game->physics->EnablePhysics(sprite1);
	//sprite1->body->CreateCircleRigidBody(40);
	//sprite1->body->CreateRectangleRigidBody(sprite1->GetWidth(), sprite1->GetHeight());
	//sprite1->body->AddForce(1, Vector(2, 1));
	//sprite1->PlayAnimation("MoveRight");
	//sprite4->PlayAnimation("MoveLeft");

	/*Matrix mat = Matrix::CreateTranslateMatrix(50, 50);
	Vector p1 = Vector(10, 10);
	Debug::Log("Mat " + mat.ToString());
	Debug::Log("Before " + p1.ToString());
	p1.TransformCord(mat);
	Debug::Log("After " + p1.ToString());*/
}
void TestState::Update()
{
	//// Test translate 4 directions
	//if (KeyDown(DIK_LEFT))
	//	sprite1->SetX(sprite1->GetX() - 1);
	//if (KeyDown(DIK_RIGHT))
	//	sprite1->SetX(sprite1->GetX() + 1);
	//if (KeyDown(DIK_UP))
	//	sprite1->SetY(sprite1->GetY() - 1);
	//if (KeyDown(DIK_DOWN))
	//	sprite1->SetY(sprite1->GetY() + 1);

	//// Test press mouse button (right click - understand)
	//MouseButtonPress(VK_LBUTTON);


	/*sprite3->SetX(sprite3->GetX() + 1);
	sprite3->SetY(sprite3->GetY() + 1);*/
	//sprite1->SetX(sprite1->GetX() + 1);
	/*sprite4->SetX(sprite4->GetX() - 1);*/
	//Debug::Log(sprite1->GetPosition().ToString());
	/*sprite1->SetRotate(sprite1->GetRotate() + 0.01*3.14);
	sprite1->SetScale(sprite1->GetScale().x*1.005, sprite1->GetScale().y*1.005);*/
	//sprite2->SetScale(sprite2->GetScale().x*1.005, sprite2->GetScale().y*1.005);
	//sprite2->SetRotate(sprite2->GetRotate() + 0.01*3.14);

	//sprite2->body->IncrementForce(5*game->logicTimer.getDeltaTime());
	//Vector scale = spriteBat2->GetScale();
	//if (scale.y < 0) {
	//	test *= -1;
	//}
	//spriteBat2->SetScale(scale.x, scale.y + test);
	if(ball->position.y<spriteBat2->position.y) spriteBat2->position.y-= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
	else if(ball->position.y>spriteBat2->position.y) {
		spriteBat2->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
	}
	if (game->GetInput()->KeyDown(DIK_Q)) {
		game->stateManager->Start("MenuState", true, true);
	}
}
void TestState::PreRender()
{
}
void TestState::Render()
{
	//sprite2->body->Render();
	sprite3->body->Render();
	spriteBat2->body->Render();
	//game->physics->CheckBound(sprite2, sprite3);
	//game->physics->CheckBound(sprite2, spriteBat2);
	for (std::list<Sprite*>::iterator it = ballList.begin(); it != ballList.end(); ++it) {
		game->physics->CheckBound(sprite3, (*it));
		game->physics->CheckBound(spriteBat2, (*it));
	}
	Debug::Log(game->frameRateReal);
}
void TestState::Pause()
{
}
void TestState::Resume()
{
}
void TestState::ShutDown()
{
	ballList.clear();
}

void TestState::CreateBall(Vector position, Vector direction)
{
	Sprite *sprite = this->add->Sprite(position.x, position.y, "ball", 0, group);
	ball = sprite;
	game->physics->EnablePhysics(sprite);
	sprite->events->onCollide = [this](GameObject *go, ColliderArg e) {
		if (e.blockDirection.left) go->position.x += 5;
		else if (e.blockDirection.right) go->position.x -= 5;
		else if (e.blockDirection.up) go->position.y += 5;
		else if (e.blockDirection.down) go->position.y -= 5;
		Vector n = e.normalSurfaceVector;
		Vector d = go->body->velocity;
		Vector r = d - 2 * (Vector::DotProduct(d, n))*n;
		go->body->velocity = r;
		go->SetPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);


	};
	//sprite2->body->CreateCircleRigidBody(sprite2->GetWidth() / 2);
	sprite->body->CreateRectangleRigidBody(sprite->GetWidth(), sprite->GetHeight());
	sprite->body->AddForce(5, direction);
	ballList.push_back(sprite);
}
