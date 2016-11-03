#include "PingPongState.h"
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
	this->preload->Texture("bat", "Resource/PingPong/bat.png");
	this->preload->Texture("ball", "Resource/PingPong/ball.png");
	this->preload->Texture("background", "Resource/PingPong/bg_2.png");
}
void PingPongState::Create()
{
	group = this->add->Group();

#pragma region Ball
	Sprite *background = this->add->Sprite(GAME_WIDTH / 2.0, GAME_HEIGHT / 2.0, "background", group);
	background->SetScale(Vector(0.8, 0.8));
	for (int i = 0; i < 1500; ++i){
	//int i = 100;
		ball = this->add->Sprite(GAME_WIDTH / 2.0, GAME_HEIGHT / 2.0, "ball", group);
		game->physics->EnablePhysics(ball);
		ball->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
			go->SetPosition(GAME_WIDTH / 2, GAME_HEIGHT / 2);
			/*if (!e.blockDirection.up && !e.blockDirection.down)
			{
			srand(time(NULL));
			Vector velocity = { (rand() % 50)*1.0f, (rand() % 50)*1.0f };
			go->body->velocity = velocity;
			}*/
			/*if (e.blockDirection.left)
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
			}*/
		};


		//ball->events->onCollide = [this](GameObject *go, ColliderArg e) {
		//	Vector velocity = go->body->velocity;
		//	float movePosition = 5;
		//	if (e.blockDirection.left) go->position.x += 5;
		//	else if (e.blockDirection.right) go->position.x -= 5;
		//	else if (e.blockDirection.up) go->position.y += 5;
		//	else if (e.blockDirection.down) go->position.y -= 5;
		//	Vector n = e.normalSurfaceVector;
		//	Vector d = velocity;
		//	Vector r = d - 2 * (Vector::DotProduct(d, n))*n;
		//	go->body->velocity = r;
		//	/*if (e.remainingTime > 0.0f) {
		//		go->position.x += r.x*e.remainingTime;
		//		go->position.y += r.y*e.remainingTime;
		//	}*/
		//};
		ball->body->CreateRectangleRigidBody(ball->GetWidth(), ball->GetHeight());
		ball->body->AddForce((float)i/1000, i);
	}
#pragma endregion Ball

	

#pragma region Bat
	int distant = 100;
	leftBat = this->add->Sprite(GAME_WIDTH/2.0, GAME_HEIGHT / 2.0, "bat",group);
	leftBat->name = "Left Bat";
	leftBat->position.x = leftBat->GetWidth() / 2 ;
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

	rightBat = this->add->Sprite(GAME_WIDTH - leftBat->GetWidth() / 2, GAME_HEIGHT / 2.0, "bat", group);
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
	/*ball->body->CheckCollisionTo(leftBat);
	ball->body->CheckCollisionTo(rightBat);*/
#pragma endregion Bat
	rightBat->body->allowBounciness = false;
	leftBat->body->allowBounciness = false;
	rightBat->body->allowWorldBlock = true;
	leftBat->body->allowWorldBlock = true;


	//ball->events->onCollide = [this](GameObject *go, ColliderArg e) {
	//	//g_debug.Log("Collided found with " + e.colliderObject->name);
	//	//if (e.colliderObject->name == rightBat->name) {
	//	//	ggEngine::Rectangle *rect = dynamic_cast<ggEngine::Rectangle*>(e.colliderObject->body->rigidBody);
	//	//	g_debug.Log(rect->p1.ToString());
	//	//}
	//	Vector velocity = go->body->velocity;
	//	double movePosition = 5;
	//	if (e.blockDirection.left) go->position.x += 5;
	//	else if (e.blockDirection.right) go->position.x -= 5;
	//	else if (e.blockDirection.up) go->position.y += 5;
	//	else if (e.blockDirection.down) go->position.y -= 5;
	//	Vector n = e.normalSurfaceVector;
	//	Vector d = velocity;
	//	Vector r = d - 2 * (Vector::DotProduct(d, n))*n;
	//	go->body->velocity = r;
	//	/*if (e.remainingTime > 0.0f) {
	//		go->position.x += r.x*e.remainingTime;
	//		go->position.y += r.y*e.remainingTime;
	//	}*/
	//};

#pragma region Others
	// Text
	Style style;
	style.fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	//style.fontColor = D3DCOLOR_ARGB(255,120, 180, 210);
	textScore1 = this->add->Text(GAME_WIDTH / 2.0 - 80, GAME_HEIGHT/2.0, "default",200,200, std::to_string(score1), style, group);
	textScore1->SetAnchor(0.5, 0.5);
	textScore2 = this->add->Text(GAME_WIDTH / 2.0 + 80, GAME_HEIGHT/2.0, "default",200,200, std::to_string(score2), style, group);
	textScore2->SetAnchor(0.5, 0.5);
	textScore1->SetScale(Vector(3, 3));
	textScore2->SetScale(Vector(3, 3));

	Style style2;
	style.fontColor = D3DCOLOR_ARGB(255, 30, 30, 30);
	this->add->Text(150, 50, "default",200,200, "W-S", style, group);
	this->add->Text(GAME_WIDTH - 150, 50, "default",200,200, "Up-Down", style, group);

#pragma endregion Others
}
void PingPongState::Update()
{
	//Sleep(1000);
	textScore1->SetText(std::to_string(score1));
	textScore2->SetText(std::to_string(score2));
	if (isSingle) {
		/*if (ball->position.y<leftBat->position.y)
			leftBat->position.y -= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		else if (ball->position.y>leftBat->position.y) {
			leftBat->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}*/
		/*if (ball->position.y<rightBat->position.y)
			rightBat->position.y -= MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		else if (ball->position.y>rightBat->position.y) {
			rightBat->position.y += MoveSpeedPerSec * (game->logicTimer.getDeltaTime());
		}*/
	
	}
	ball->body->Render();
	rightBat->body->Render();
	leftBat->body->Render();
	if (game->GetInput()->KeyDown(DIK_Q)) {
		game->stateManager->Start("MenuState", true, true);
	}
}
void PingPongState::PreRender()
{
}
void PingPongState::Render()
{
	//ball->body->Render();
	//leftBat->body->Render();
	//rightBat->body->Render();
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
