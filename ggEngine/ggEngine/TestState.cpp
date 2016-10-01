#include "TestState.h"
#include "Add.h"
#include "Preload.h"
#include "Game.h"
#include "Physics.h"
#include "Body.h"
#include "DXInput.h"
#include "Events.h"
#include "ColliderArg.h"
Sprite *spriteBat2;
Sprite *background;
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
	this->test = 0;
	Group* group = this->add->Group();
	background = this->add->Sprite(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0, "girl", 0, group);
	background->SetWidth(WINDOW_WIDTH);
	background->SetHeight(WINDOW_HEIGHT);
	sprite2 = this->add->Sprite(20, 20, "ball", 0, group);
	game->physics->EnablePhysics(sprite2);
	sprite2->events->onCollide = [this](GameObject *go, ColliderArg e){
		if (e.blockDirection.left) go->position.x += 5;
		else if (e.blockDirection.right) go->position.x -= 5;
		else if (e.blockDirection.up) go->position.y += 5;
		else if (e.blockDirection.down) go->position.y -= 5;
		Vector n = e.normalSurfaceVector;
		Vector d = go->body->velocity;
		Vector r = d - 2 * (Vector::DotProduct(d, n))*n;
		go->body->velocity = r;


	};
	//sprite2->body->CreateCircleRigidBody(sprite2->GetWidth() / 2);
	sprite2->body->CreateRectangleRigidBody(sprite2->GetWidth(), sprite2->GetHeight());
	sprite2->body->AddForce(5 , Vector(3, 4));
	sprite3 = this->add->Sprite(WINDOW_WIDTH / 20.0, WINDOW_HEIGHT / 2.0, "bat", 0, group);
	sprite3->position.x = sprite3->GetWidth() / 2;
	game->physics->EnablePhysics(sprite3);
	sprite3->body->CreateRectangleRigidBody(sprite3->GetWidth(), sprite3->GetHeight());

	spriteBat2 = this->add->Sprite(WINDOW_WIDTH - sprite3->GetWidth()/2, WINDOW_HEIGHT / 2.0, "bat", 0, group);

	game->physics->EnablePhysics(spriteBat2);
	spriteBat2->body->CreateRectangleRigidBody(sprite3->GetWidth(), sprite3->GetHeight());
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
}
void TestState::PreRender()
{
}
void TestState::Render()
{
	//sprite2->body->Render();
	//sprite3->body->Render();
	game->physics->CheckBound(sprite2, sprite3);
	game->physics->CheckBound(sprite2, spriteBat2);
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